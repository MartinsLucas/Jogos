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
  static Game *instance;
  SDL_Renderer *renderer;

  Game(const char *title, int width, int height);

  void CalculateDeltaTime();

public:
  ~Game();

  void Run();
  State &GetState();
  SDL_Renderer *GetRenderer();
  static Game &GetInstance();

  float GetDeltaTime();
};
#endif
