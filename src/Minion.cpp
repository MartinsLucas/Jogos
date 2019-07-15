#define PI 3.1415926535
#define SPEED PI/120
#define MINIONS_DISTANCE 160

#include "Minion.h"
#include "Sprite.h"

Minion::Minion(GameObject &associated, std::weak_ptr<GameObject> alienCenter, float arcOffsetDegr) : Component(associated), alienCenter(*alienCenter.lock().get()) {
  this->arc = arcOffsetDegr;
  Sprite *sprite = new Sprite(associated, "assets/img/minion.png");
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
  Vec2 position = this->alienCenter.box.GetCenter().Rotate(200, this->arc);
  associated.box.SetCenter(position);
}

void Shoot(Vec2 target) {}

bool Minion::Is(const char *type) {
  if (strcmp(type, "Minion") == 0) {
    return(true);
  } else {
    return(false);
  }
}
