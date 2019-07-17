#define HP 30
#define ROTATION_SPEED -PI/300
#define MOVEMENT_SPEED 250
#define TOLERANCE 1e-5
#define PI 3.1415926535

#include "Game.h"
#include "Alien.h"
#include "State.h"
#include "Camera.h"
#include "Minion.h"
#include "Sprite.h"
#include "InputManager.h"

#include <memory>

Alien::Alien(GameObject &associated, int minionsAmount) : Component(associated) {
  Sprite *sprite = new Sprite(associated, "assets/img/alien.png");
  associated.AddComponent(sprite);

  associated.box.x = 0;
  associated.box.y = 0;
  associated.box.width = sprite->GetWidth();
  associated.box.height = sprite->GetHeight();

  this->minionsAmount = minionsAmount;
  this->hp = HP;
  this->speed = Vec2();
}

Alien::~Alien() {
  std::vector<std::weak_ptr<GameObject>> minionArray;
  for (int index = this->minionArray.size() - 1; index >= 0; --index) {
    delete this->minionArray[index].lock().get();
  }
  this->minionArray.clear();
}

void Alien::Start() {
  for (int i = 0; i < this->minionsAmount; i++) {
    GameObject *minionGameObject = new GameObject();
    std::weak_ptr<GameObject> alienCenter = Game::GetInstance().GetState().GetObjectPtr(&this->associated);

    minionGameObject->AddComponent(new Minion(
      *minionGameObject,
      alienCenter,
      (2 * PI / this->minionsAmount) * i
    ));

    this->minionArray.push_back(Game::GetInstance().GetState().AddObject(minionGameObject));
  }
}

void Alien::Render() {}

void Alien::Update(float dt) {
  this->associated.angleDeg += ROTATION_SPEED * 180/PI;
  if(InputManager::GetInstance().MousePress(LEFT_MOUSE_BUTTON)) {
    this->taskQueue.push(
      Action(
        Action::ActionType::SHOOT,
        InputManager::GetInstance().GetMouseX() + Camera::position.x,
        InputManager::GetInstance().GetMouseY() + Camera::position.y
      )
    );
  }
  if(InputManager::GetInstance().MousePress(RIGHT_MOUSE_BUTTON)) {
    this->taskQueue.push(
      Action(
        Action::ActionType::MOVE,
        InputManager::GetInstance().GetMouseX() + Camera::position.x,
        InputManager::GetInstance().GetMouseY() + Camera::position.y
      )
    );
  }
  if(this->taskQueue.size() > 0) {
    Action task = taskQueue.front();
    switch (task.type) {
      case Action::ActionType::MOVE: {
        Vec2 newPosition = this->MoveTo(task.position, dt);
        this->associated.box.SetCenter(newPosition);

        if(
          abs(task.position.x - newPosition.x) < TOLERANCE
          && abs(task.position.y - newPosition.y) < TOLERANCE
        ) {
          taskQueue.pop();
        }
        break;
      }
      case Action::ActionType::SHOOT:
        if(this->minionsAmount > 0) {
          Minion *minion = (Minion*) this->GetNearestMinion(task.position).GetComponent("Minion");
          minion->Shoot(task.position);
        }
        taskQueue.pop();
        break;
      default:
        break;
    }
  }
  if(this->hp <= 0) {
    this->associated.RequestDelete();
  }
}

GameObject& Alien::GetNearestMinion(Vec2 target) {
  GameObject *nearestMinion = this->minionArray.front().lock().get();

  for(auto &minion : this->minionArray) {
    GameObject *currentMinion = minion.lock().get();
    if(
      currentMinion->box.GetCenter().GetDistance(target)
      < nearestMinion->box.GetCenter().GetDistance(target)
    ) {
      nearestMinion = currentMinion;
    }
  }
  return(*nearestMinion);
}

Vec2 Alien::MoveTo(Vec2 target, float dt) {
  Vec2 alienPosition = this->associated.box.GetCenter();
  this->speed = alienPosition.GetDisplacementSpeed(target, MOVEMENT_SPEED);

  if(
    (alienPosition.x + this->speed.x * dt > target.x && target.x > alienPosition.x)
    || (alienPosition.x + this->speed.x * dt < target.x && target.x < alienPosition.x)
  ) {
    alienPosition.x = target.x;
  } else {
    alienPosition.x += this->speed.x * dt;
  }
  if(
    (alienPosition.y + this->speed.y * dt > target.y && target.y > alienPosition.y)
    || (alienPosition.y + this->speed.y * dt < target.y && target.y < alienPosition.y)
  ) {
    alienPosition.y = target.y;
  } else {
    alienPosition.y += this->speed.y * dt;
  }

  return(alienPosition);
}

bool Alien::Is(const char *type) {
  if (strcmp(type, "Alien") == 0) {
    return(true);
  } else {
    return(false);
  }
}

Alien::Action::Action(ActionType type, float x, float y) {
  this->type = type;
  this->position = Vec2(x, y);
}
