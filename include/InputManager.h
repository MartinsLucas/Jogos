#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H
#define INCLUDE_SDL

#define LEFT_ARROW_KEY SDLK_LEFT
#define RIGHT_ARROW_KEY SDLK_RIGHT
#define UP_ARROW_KEY SDLK_UP
#define DOWN_ARROW_KEY SDL_KEYDOWN
#define ESCAPE_KEY SDLK_ESCAPE
#define LEFT_MOUSE_BUTTON SDL_BUTTON_LEFT
#define SPACE_BAR SDLK_SPACE

#include "SDL_include.h"

#include <iostream>
#include <unordered_map>

using namespace std;

class InputManager {
private:

  int mouseX;
  int mouseY;
  int updateCounter;
  bool quitRequested;

  bool mouseState[6];
  int mouseUpdate[6];

  std::unordered_map<int, bool> keyState;
  std::unordered_map<int, int> keyUpdate;

  InputManager();
  ~InputManager();
public:

  void Update();

  int GetMouseX();
  int GetMouseY();

  bool KeyPress(int key);
  bool KeyRelease(int key);
  bool IsKeyDown(int key);

  bool MousePress(int button);
  bool MouseRelease(int button);
  bool IsMouseDown(int button);

  bool QuitRequested();

  static InputManager &GetInstance();
};
#endif
