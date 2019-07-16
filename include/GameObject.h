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
  bool started;
  double angleDeg;

  GameObject();

  ~GameObject();

  bool IsDead();

  void Start();
  void Render();
  void RequestDelete();
  void Update(float dt);
  void AddComponent(Component *component);
  void RemoveComponent(Component *component);
  Component *GetComponent(const char *type);
};
#endif
