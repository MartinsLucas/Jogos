#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <iostream>
#include <vector>

#include "Rect.h"

using namespace std;

class Component;

class GameObject {
private:
  std::vector<Component*> components;
  bool isDead;

public:
  Rect box;

  GameObject();

  ~GameObject();

  void Update(float dt);
  void Render();
  bool IsDead();
  void RequestDelete();
  void AddComponent(Component *component);
  void RemoveComponent(Component *component);
  Component *GetComponent(const char *type);
};
#endif
