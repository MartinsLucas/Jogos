#ifndef VEC2_H
#define VEC2_H

#define PI 3.1415926535

#include <iostream>
#include <cmath>

#define PI 3.1415926535

using namespace std;

class Vec2 {
public:
  float x;
  float y;

  Vec2();
  Vec2(float x, float y);

  Vec2 GetDelta(Vec2 target);
  float GetDistance(Vec2 target);
  Vec2 RandomRotation(float radius);
  Vec2 Rotate(float radius, float angle);
  Vec2 GetDisplacementSpeed(Vec2 target, float velocity);

  Vec2 operator+(const Vec2 &vec2);
  Vec2 operator+(const float &constant);
  Vec2 operator-(const Vec2 &vec2);
  Vec2 operator-(const float &constant);
  Vec2 operator*(const float &constant);

  /*
  Basic vector operations such as:
    Magnitude
    Normalization
    Distance between points
    Inclination
    Rotation
    etc
  See "Trabalho 2 section 1"
  */
};
#endif
