#define HP 30
#define SPEED 250
#define TOLERANCE 1e-5


#include "Alien.h"
#include "Camera.h"
#include "Sprite.h"
#include "InputManager.h"

Alien::Alien(GameObject &associated, int minionsAmount) : Component(associated) {
  Sprite *sprite = new Sprite(associated, "assets/img/alien.png");
  associated.AddComponent(sprite);

  associated.box.x = 0;
  associated.box.y = 0;
  associated.box.width = sprite->GetWidth();
  associated.box.height = sprite->GetHeight();


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

void Alien::Start() {}

void Alien::Render() {}

void Alien::Update(float dt) {
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
Vec2 Alien::MoveTo(Vec2 target, float dt) {
  Vec2 alienPosition = this->associated.box.GetCenter();
  this->speed = alienPosition.GetDisplacementSpeed(target, SPEED);

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
