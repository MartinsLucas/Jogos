#ifndef CAMERA_FOLLOWER_H
#define CAMERA_FOLLOWER_H

#include <iostream>

#include "Vec2.h"
#include "Component.h"
#include "GameObject.h"

using namespace std;

class CameraFollower : public Component {
public:
  CameraFollower(GameObject &gameObject);

  void Render();
  void Update(float dt);
  bool Is(const char *type);
};
#endif
