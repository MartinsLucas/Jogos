#include "CameraFollower.h"
#include "Camera.h"

CameraFollower::CameraFollower(GameObject &gameObject) : Component(gameObject) {}

void CameraFollower::Render() {}

void CameraFollower::Update(float dt) {
  this->associated.box.x = Camera::position.x;
  this->associated.box.y = Camera::position.y;
}

void CameraFollower::Start() {}

bool CameraFollower::Is(const char *type) {
  if (strcmp(type, "CameraFollower") == 0) {
    return(true);
  } else {
    return(false);
  }
}
