#define PI 3.1415926535
#define SPEED PI/240

#define PENGUIN_HP 100
#define LINEAR_SPEED_LIMIT 400
#define PENGUIN_ACELERATION 500
#define ANGULAR_ACELERATION 5

#include "Game.h"
#include "Minion.h"
#include "PenguinBody.h"
#include "PenguinCannon.h"

PenguinBody *PenguinBody::player = nullptr;

PenguinBody::PenguinBody(GameObject &associated) : Component(associated) {
  Sprite *sprite = new Sprite(associated, "assets/img/penguin.png");
  associated.AddComponent(sprite);

  this->hp = PENGUIN_HP;
  this->angle = 0;
  this->linearSpeed = 0;
  this->speed = Vec2(0, 0);
  PenguinBody::player = this;
}

PenguinBody::~PenguinBody() {
  PenguinBody::player = nullptr;
  delete this->penguinCannon.lock().get();
}

// FIXME!
void PenguinBody::Start() {
  // GameObject *penguinCannonGameObject = new GameObject();
  //
  // penguinCannonGameObject->AddComponent(new PenguinCannon(
  //   *penguinCannonGameObject,
  //   Game::GetInstance().GetState().GetObjectPtr(&this->associated)
  // ));
  //
  // penguinCannonGameObject->box.SetCenter(Vec2(504.0, 640.0));
  // Game::GetInstance().GetState().AddObject(penguinCannonGameObject);
}

void PenguinBody::Render() {}

void PenguinBody::Update(float dt) {
  if(this->hp <= 0) {
    this->associated.RequestDelete();
    this->penguinCannon.lock().get()->RequestDelete();
  }

  if(InputManager::GetInstance().IsKeyDown(W_KEY)) {
    this->linearSpeed += PENGUIN_ACELERATION * dt;
    if(this->linearSpeed > LINEAR_SPEED_LIMIT) {
      this->linearSpeed = LINEAR_SPEED_LIMIT;
    }
  }
  if(InputManager::GetInstance().IsKeyDown(S_KEY)) {
    this->linearSpeed -= (PENGUIN_ACELERATION) * dt;
    if(this->linearSpeed < ((LINEAR_SPEED_LIMIT / 2) * -1)) {
      this->linearSpeed = (LINEAR_SPEED_LIMIT / 2) * -1;
    }
  }
  if(InputManager::GetInstance().IsKeyDown(A_KEY)) {
    this->angle -= ANGULAR_ACELERATION * dt;
  }
  if(InputManager::GetInstance().IsKeyDown(D_KEY)) {
    this->angle += ANGULAR_ACELERATION * dt;
  }

  this->associated.angleDeg = this->angle * (180 / PI);
  this->speed = Vec2::GetSpeed(this->angle) * this->linearSpeed;

  this->associated.box.x += this->speed.x * dt;
  this->associated.box.y += this->speed.y * dt;
}

bool PenguinBody::Is(const char *type) {
  if (strcmp(type, "PenguinBody") == 0) {
    return(true);
  } else {
    return(false);
  }
}
