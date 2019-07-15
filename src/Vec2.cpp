#include "Vec2.h"

Vec2::Vec2() {
  this->x = 0;
  this->y = 0;
}

Vec2::Vec2(int x, int y) {
  this->x = x;
  this->y = y;
}

Vec2 Vec2::Rotate(float radius, float angle) {
  int newXValue = this->x + (radius * cos(angle));
  int newYValue = this->y + (radius * sin(angle));

  return(Vec2(newXValue, newYValue));
}

Vec2 Vec2::RandomRotation(float radius) {
  float randomAngle = -PI + PI * (rand() % 1001)/500.0;
  return(this->Rotate(radius, randomAngle));
}

Vec2 Vec2::operator+(const Vec2 &vec2) {
  return (Vec2(this->x + vec2.x, this->y + vec2.y));
}

Vec2 Vec2::operator+(const float &constant) {
  return (Vec2(this->x + constant, this->y + constant));
}

Vec2 Vec2::operator-(const Vec2 &vec2) {
  return (Vec2(this->x - vec2.x, this->y - vec2.y));
}

Vec2 Vec2::operator-(const float &constant) {
  return (Vec2(this->x - constant, this->y - constant));
}

Vec2 Vec2::operator*(const float &constant) {
  return (Vec2(this->x * constant, this->y * constant));
}
