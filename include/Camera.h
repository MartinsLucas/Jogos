#ifndef CAMERA_H
#define CAMERA_H

#include <iostream>

#include "Vec2.h"
#include "GameObject.h"

using namespace std;

class Camera {
private:
  static GameObject *focus;

public:
  static Vec2 speed;
  static Vec2 position;

  static void Follow(GameObject *newFocus);
  static void Unfollow();
  static void Update(float dt);
};
#endif
