#ifndef VEC2_H
#define VEC2_H

#define PI 3.1415926535

#include <iostream>
#include <math.h>

using namespace std;

class Vec2 {
private:
  int x;
  int y;

public:
  Vec2();
  Vec2(int x, int y);

  int GetXValue();
  int GetYValue();
  Vec2 GetRotated(float angle);

  Vec2 operator+(const Vec2 &vec2);
  Vec2 operator+(const float &constant);
  Vec2 operator-(const Vec2 &vec2);
  Vec2 operator-(const float &constant);
  Vec2 operator*(const float &constant);
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
