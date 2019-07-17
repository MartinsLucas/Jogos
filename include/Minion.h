#ifndef MINION_H
#define MINION_H

#include <iostream>
#include <memory>

#include "Component.h"
#include "GameObject.h"

using namespace std;

class Minion : public Component {
private:
  float arc;
  GameObject& alienCenter;

public:
  Minion(GameObject &associated, std::weak_ptr<GameObject> alienCenter, float arcOffsetDegr = 0);

  void Start();
  void Render();
  void Update(float dt);
  void Shoot(Vec2 target);
  bool Is(const char *type);
};
#endif
