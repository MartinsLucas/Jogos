#include "Rect.h"

Rect::Rect() {
  this->x = 0;
  this->y = 0;
  this->width = 0;
  this->height = 0;
}

Rect::Rect(float x, float y, float width, float height) {
  this->x = x;
  this->y = y;
  this->width = width;
  this->height = height;
}

bool Rect::Contains(float xPosition, float yPosition) {
  return this->WithinXLimits(xPosition) and this->WithinYLimits(yPosition);

}

bool Rect::WithinXLimits(float xPosition) {
  return(this->x <= xPosition and xPosition <= (this->x + this->width));
}

bool Rect::WithinYLimits(float yPosition) {
  return((this->y <= yPosition) and (yPosition <= (this->y + this->height)));
}

Vec2 Rect::GetCenter() {
  return(Vec2(this->x + (this->width / 2.0), this->y + (this->height / 2.0)));
}

void Rect::SetCenter(Vec2 center) {
  this->x = center.x - (this->width / 2.0);
  this->y = center.y - (this->height / 2.0);
}
