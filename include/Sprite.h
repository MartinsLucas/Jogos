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
  SDL_Rect clipRect;
  SDL_Texture *texture;

  Vec2 scale;

public:
  Sprite(GameObject &associated);
  Sprite(GameObject &associated, const char *file);

  void Start();
  void Render();
  void Render(int xPosition, int yPosition);
  void Update(float dt);
  void Open(const char *file);
  void SetClip(int x, int y, int width, int height);
  int GetWidth();
  int GetHeight();
  bool IsOpen();
  bool Is(const char *type);
  Vec2 GetScale();
  void SetScaleX(float scaleX, float scaleY);
};
#endif
