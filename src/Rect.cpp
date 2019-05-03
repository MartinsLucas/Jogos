#include "Rect.h"

Rect::Rect() {
  this->x = 0;
  this->y = 0;
  this->width = 0;
  this->height = 0;
}

Rect::Rect(int x, int y, int width, int height) {
  this->x = x;
  this->y = y;
  this->width = width;
  this->height = height;
}

bool Rect::Contains(float mouseX, float mouseY) {
  return (true);
}

int Rect::GetXPosition() {
  return(this->x);
}

int Rect::GetYPosition() {
  return(this->y);
}

void Rect::SetXPosition(int position) {
  this->x = position;
}

void Rect::SetYPosition(int position) {
  this->y = position;
}

void Rect::SetWidth(int width) {
  this->width = width;
}

void Rect::SetHeight(int height) {
  this->height = height;
}
