#ifndef BULLET_H
#define BULLET_H

#include <iostream>
#include <memory>

#include "Component.h"
#include "GameObject.h"

using namespace std;

class Bullet : public Component {
private:
  int damage;
  Vec2 speed;
  float distanceLeft;

public:
  Bullet(GameObject &associated, float angle, float speed, int damage, float maxDistance, const char* sprite);

  void Start();
  void Render();
  void Update(float dt);

  int GetDamage();
  bool Is(const char *type);
};
#endif
