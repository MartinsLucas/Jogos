#include "Face.h"

Face::Face(GameObject &associated) : Component(associated) {
  this->hitpoints = 30;
}

void Face::Damage(int damage) {
  this->hitpoints -= damage;

  if(this->hitpoints <= 0) {
    this->associated.RequestDelete();
  }
}

void Face::Render() {
  printf("Face Rendered!\n");
}

void Face::Update(float delta) {
  printf("Face Updated!\n");
}

bool Face::Is(const char *type) {
  if (strcmp(type, "Face") == 0) {
    return(true);
  } else {
    return(false);
  }
}
