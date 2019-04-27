#ifndef FACE_H
#define FACE_H

#include <iostream>

#include "Component.h"

using namespace std;

class Face : public Component {
private:
  int hitpoints;

public:
  Face(GameObject &associated);

  void Damage(int damage);
  void Render();
  void Update(float delta);
  bool Is(const char *type);
};
#endif