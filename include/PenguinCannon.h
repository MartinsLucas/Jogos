#ifndef PENGUIN_CANNON_H
#define PENGUIN_CANNON_H

#include <iostream>
#include <memory>

#include "Component.h"
#include "PenguinBody.h"
#include "GameObject.h"

using namespace std;

class PenguinCannon : public Component {
private:
  float angle;
  Vec2 cannonCenter;
  std::weak_ptr<GameObject> penguinBody;

public:
  PenguinCannon(GameObject &associated, std::weak_ptr<GameObject> penguinBody);

  void Shoot();
  void Start();
  void Render();
  void Update(float dt);
  void UpdatePosition();
  bool Is(const char *type);
};
#endif
