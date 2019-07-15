#include "Camera.h"

#include "Game.h"

Vec2 Camera::speed = Vec2(250, 250);
GameObject *Camera::focus = nullptr;
Vec2 Camera::position = Vec2();

void Camera::Update(float dt) {
  if (focus != nullptr) {
    position.x = focus->box.GetCenter().x - (Game::screenWidth / 2);
    position.y = focus->box.GetCenter().y - (Game::screenHeight / 2);
  } else {
    if(InputManager::GetInstance().IsKeyDown(UP_ARROW_KEY)) {
      position.y -= speed.y * dt;
    }
		if(InputManager::GetInstance().IsKeyDown(DOWN_ARROW_KEY)) {
      position.y += speed.y * dt;
    }
		if(InputManager::GetInstance().IsKeyDown(LEFT_ARROW_KEY)) {
      position.x -= speed.x * dt;
    }
		if(InputManager::GetInstance().IsKeyDown(RIGHT_ARROW_KEY)) {
      position.x += speed.x * dt;
    }
  }
}

void Camera::Follow(GameObject *newFocus) {
  focus = newFocus;
}

void Camera::Unfollow() {
  focus = nullptr;
}
