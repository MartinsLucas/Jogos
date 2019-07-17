#ifndef PENGUIN_BODY_H
#define PENGUIN_BODY_H

#include <iostream>
#include <memory>

#include "Vec2.h"
#include "Component.h"
#include "GameObject.h"

using namespace std;

class PenguinBody : public Component {
private:
  int hp;
  float angle;
  float linearSpeed;
  Vec2 speed;
  std::weak_ptr<GameObject> penguinCannon;

public:
  static PenguinBody *player;

  PenguinBody(GameObject &associated);
  ~PenguinBody();

  void Start();
  void Render();
  void Update(float dt);
  bool Is(const char *type);
};
#endif
