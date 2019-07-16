#ifndef SPRITE_H
#define SPRITE_H

#define INCLUDE_SDL_IMAGE
#include "SDL_include.h"

#include <iostream>

#include "Vec2.h"
#include "Component.h"
#include "Resources.h"

using namespace std;

class Sprite : public Component {
private:
  int width;
  int height;
  int frameCount;
  int currentFrame;

  Vec2 scale;

  float frameTime;
  float timeElapsed;

  SDL_Rect clipRect;
  SDL_Texture *texture;


public:
  Sprite(GameObject &associated);
  Sprite(GameObject &associated, const char *file, int frameCount = 1, float frameTime = 1);

  void Start();
  void Render();
  void UpdateBox();
  void Update(float dt);
  void SetFrame(int frame);
  void Open(const char *file);
  void SetFrameTime(float frameTime);
  void SetFrameCount(int frameCount);
  void Render(int xPosition, int yPosition);
  void SetScaleX(float scaleX, float scaleY);
  void SetClip(int x, int y, int width, int height);


  int GetWidth();
  int GetHeight();
  bool IsOpen();
  bool Is(const char *type);

  Vec2 GetScale();
};
#endif
