#ifndef COMPONENT_H
#define COMPONENT_H

#include <iostream>
#include <string.h>

#include "GameObject.h"

using namespace std;

class Component {
protected:
  GameObject &associated;

public:
  Component(GameObject &associated);

  virtual ~Component();
  virtual void Update(float delta) = 0;
  virtual void Render() = 0;
  virtual bool Is(const char *type) = 0;
};
#endif
