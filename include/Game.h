#ifndef GAME_H
#define GAME_H
#define INCLUDE_SDL
#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER

#include <iostream>

#include "SDL_include.h"

#include "State.h"

using namespace std;

class Game {
private:
  float dt;
  int frameStart;
  State *state;
  SDL_Window *window;
  SDL_Renderer *renderer;

  static Game *instance;

  Game(const char *title, int width, int height);

  void CalculateDeltaTime();

public:
  static int screenWidth;
  static int screenHeight;

  ~Game();

  void Run();
  State &GetState();
  SDL_Renderer *GetRenderer();
  static Game &GetInstance();

  float GetDeltaTime();

  static int GetScreenWidth();
  static int GetScreenHeight();
};
#endif
