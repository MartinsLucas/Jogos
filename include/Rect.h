#ifndef RECT_H
#define RECT_H

#include <iostream>
#include <math.h>

using namespace std;

class Rect {
private:
  int x;
  int y;
  int width;
  int height;

public:
  Rect();
  Rect(int x, int y, int width, int height);

  int GetXPosition();
  int GetYPosition();
  void SetXPosition(int position);
  void SetYPosition(int position);
  void SetWidth(int width);
  void SetHeight(int height);
  bool Contains(float mouseX, float mouseY);
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
