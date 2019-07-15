#include "Face.h"
#include "Camera.h"

#include <typeinfo>

Face::Face(GameObject &associated) : Component(associated) {
  this->hitpoints = 30;
}

void Face::Damage(int damage) {
  this->hitpoints -= damage;

  if(this->hitpoints <= 0) {
    this->associated.RequestDelete();

    Sound *sound = (Sound*)this->associated.GetComponent("Sound");

    if (this->associated.IsDead()) {
    }

    if ( nullptr != sound ) {
      sound->Play();
    }
  }
}

void Face::Render() {}

void Face::Update(float dt) {
  if(this->associated.box.Contains(
      InputManager::GetInstance().GetMouseX() + Camera::position.x,
      InputManager::GetInstance().GetMouseY() + Camera::position.y
  )) {
    if(InputManager::GetInstance().MousePress(LEFT_MOUSE_BUTTON))
		  this->Damage(std::rand() % 10 + 10);
	}
}

bool Face::Is(const char *type) {
  if (strcmp(type, "Face") == 0) {
    return(true);
  } else {
    return(false);
  }
}
