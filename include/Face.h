#ifndef FACE_H
#define FACE_H

#include <iostream>

#include "Sound.h"
#include "Component.h"
#include "InputManager.h"

using namespace std;

class Face : public Component {
private:
  int hitpoints;

public:
  Face(GameObject &associated);

  void Start();
  void Render();
  void Update(float dt);
  void Damage(int damage);
  bool Is(const char *type);
};
#endif
