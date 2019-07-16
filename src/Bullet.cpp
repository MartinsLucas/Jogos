#define PI 3.1415926535

#include "Game.h"
#include "Alien.h"
#include "Bullet.h"
#include "Sprite.h"
#include "Camera.h"
#include "Sprite.h"
#include "InputManager.h"

#include <memory>

Bullet::Bullet(GameObject &associated, float angle, float speed, int damage, float maxDistance, const char* sprite) : Component (associated) {
  Sprite *bulletSprite = new Sprite(associated, sprite);
  associated.AddComponent(bulletSprite);

  associated.box.width = bulletSprite->GetWidth();
  associated.box.height = bulletSprite->GetHeight();
  this->associated.angleDeg = angle * 180 / PI;

  this->damage = damage;
  this->speed = Vec2::GetSpeed(angle) * speed;
  this->distanceLeft = maxDistance;
}

int Bullet::GetDamage() {
  return(this->damage);
}

void Bullet::Start() {}

void Bullet::Render() {}

void Bullet::Update(float dt) {
  if(this->distanceLeft > 0) {
    Vec2 currentPosition = this->associated.box.GetCenter();

    this->associated.box.SetCenter(Vec2(
      currentPosition.x + this->speed.x * dt,
      currentPosition.y + this->speed.y * dt
    ));
    this->distanceLeft -= currentPosition.GetDistance(this->associated.box.GetCenter());
  } else {
    this->associated.RequestDelete();
  }
}

bool Bullet::Is(const char *type) {
  if (strcmp(type, "Bullet") == 0) {
    return(true);
  } else {
    return(false);
  }
}
