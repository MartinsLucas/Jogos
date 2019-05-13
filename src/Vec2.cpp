#include "Vec2.h"
#include <cmath>

Vec2::Vec2() {
  this->x = 0;
  this->y = 0;
}

Vec2::Vec2(int x, int y) {
  this->x = x;
  this->y = y;
}

int Vec2::GetXValue() {
  return (this->x);
}
int Vec2::GetYValue() {
  return (this->y);
}

Vec2 Vec2::Rotate(float radius, float angle) {
  int newXValue = this->x + (radius * cos(angle));
  int newYValue = this->y + (radius * sin(angle));

  return(Vec2(newXValue, newYValue));
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
