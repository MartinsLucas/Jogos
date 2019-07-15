#ifndef RECT_H
#define RECT_H

#include <iostream>
#include <math.h>

#include "Vec2.h"

using namespace std;

class Rect {
public:
  int x;
  int y;
  int width;
  int height;

  Rect();
  Rect(int x, int y, int width, int height);

  bool Contains(float mouseX, float mouseY);
  bool WithinXLimits(float xPosition);
  bool WithinYLimits(float yPosition);

  Vec2 GetCenter();
  void SetCenter(Vec2 center);
  /*
  Basic vector operations such as:
    Sum and subtraction
    Scalar vector multiplication
    Magnitude
    Normalization
    Distance between points
    Inclination
    Rotation
    Finding the rect center
    etc
  See "Trabalho 2 section 1"
  */
};
#endif
