#include "Vec2.h"

Vec2::Vec2() {
  this->x = 0;
  this->y = 0;
}

Vec2::Vec2(int x, int y) {
  this->x = x;
  this->y = y;
}

int Vec2::GetXPosition() {
  return (this->x);
}
int Vec2::GetYPosition() {
  return (this->y);
}
