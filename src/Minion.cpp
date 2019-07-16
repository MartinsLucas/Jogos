#define PI 3.1415926535
#define SPEED PI/120

#define MINIONS_DISTANCE 160
#define BULLET_SPEED 300
#define BULLET_DAMAGE 25
#define BULLET_MAX_DISTANCE 500

#include "Game.h"
#include "Minion.h"
#include "Sprite.h"
#include "Bullet.h"

Minion::Minion(GameObject &associated, std::weak_ptr<GameObject> alienCenter, float arcOffsetDegr) : Component(associated), alienCenter(*alienCenter.lock().get()) {
  this->arc = arcOffsetDegr;
  Sprite *sprite = new Sprite(associated, "assets/img/minion.png");

  float randomScale = (0.1 * (std::rand() % 6)) + 1;
  sprite->SetScaleX(randomScale, randomScale);

  associated.AddComponent(sprite);

  Vec2 initialPosition = this->alienCenter.box.GetCenter().Rotate(MINIONS_DISTANCE, arcOffsetDegr);

  associated.box.SetCenter(initialPosition);
  associated.box.width = sprite->GetWidth();
  associated.box.height = sprite->GetHeight();
}

void Minion::Start() {}

void Minion::Render() {}

void Minion::Update(float dt) {
  this->arc += SPEED;
  this->associated.angleDeg = (this->arc * 180/PI);
  if(&this->alienCenter != nullptr) {
    Vec2 position = this->alienCenter.box.GetCenter().Rotate(200, this->arc);
    associated.box.SetCenter(position);
  } else {
    this->associated.RequestDelete();
  }
}

void Minion::Shoot(Vec2 target) {
  GameObject *bulletGameObject = new GameObject();
  float speed = this->associated.box.GetCenter().GetAngle(target);
  bulletGameObject->AddComponent(new Bullet(*bulletGameObject, speed, BULLET_SPEED, BULLET_SPEED, BULLET_MAX_DISTANCE, "assets/img/minionbullet1.png"));
  bulletGameObject->box.SetCenter(this->associated.box.GetCenter());

  Game::GetInstance().GetState().AddObject(bulletGameObject);
}

bool Minion::Is(const char *type) {
  if (strcmp(type, "Minion") == 0) {
    return(true);
  } else {
    return(false);
  }
}
