#define BULLET_SPEED 600
#define BULLET_DAMAGE 25
#define BULLET_MAX_DISTANCE 500

#include "Game.h"
#include "Camera.h"
#include "Bullet.h"
#include "Sprite.h"
#include "InputManager.h"
#include "PenguinCannon.h"

PenguinCannon::PenguinCannon(GameObject &associated, std::weak_ptr<GameObject> penguinBody) : Component(associated) {
  Sprite *sprite = new Sprite(associated, "assets/img/cubngun.png");
  associated.AddComponent(sprite);

  this->angle = 0;
  this->penguinBody = penguinBody;

  this->UpdatePosition();
}

void PenguinCannon::Start() {}

void PenguinCannon::Render() {}

void PenguinCannon::Update(float dt) {
  this->UpdatePosition();

  Vec2 mousePosition = Vec2(
    InputManager::GetInstance().GetMouseX() + Camera::position.x,
    InputManager::GetInstance().GetMouseY() + Camera::position.y
  );

  this->angle = this->cannonCenter.GetAngle(mousePosition);
  this->associated.angleDeg = this->angle * (180 / PI);

  if(InputManager::GetInstance().MousePress(LEFT_MOUSE_BUTTON)) {
    this->Shoot();
  }
}

void PenguinCannon::UpdatePosition() {
  this->associated.box.SetCenter(this->penguinBody.lock().get()->box.GetCenter());
  this->cannonCenter = this->associated.box.GetCenter() + Vec2(55, 25);
}

void PenguinCannon::Shoot() {
  GameObject *bulletGameObject = new GameObject();
  bulletGameObject->AddComponent(new Bullet(*bulletGameObject, this->angle, BULLET_SPEED, BULLET_DAMAGE, BULLET_MAX_DISTANCE, "assets/img/minionbullet2.png"));
  bulletGameObject->box.SetCenter(cannonCenter.Rotate(65, this->angle));

  Game::GetInstance().GetState().AddObject(bulletGameObject);
}

bool PenguinCannon::Is(const char *type) {
  if (strcmp(type, "PenguinBody") == 0) {
    return(true);
  } else {
    return(false);
  }
}
