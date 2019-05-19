#ifndef SPRITE_H
#define SPRITE_H

#define INCLUDE_SDL_IMAGE
#include "SDL_include.h"

#include <iostream>

#include "Component.h"
#include "Resources.h"

using namespace std;

class Sprite : public Component {
private:
  SDL_Texture *texture;
  SDL_Rect clipRect;
  int width;
  int height;

public:
  Sprite(GameObject &associated);
  Sprite(GameObject &associated, const char *file);

  void Render();
  void Render(int xPosition, int yPosition);
  void Update(float delta);
  void Open(const char *file);
  void SetClip(int x, int y, int width, int height);
  int GetWidth();
  int GetHeight();
  bool IsOpen();
  bool Is(const char *type);
};
#endif
