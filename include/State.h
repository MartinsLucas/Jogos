#ifndef STATE_H
#define STATE_H

#include <iostream>
#include <string>

#include "Sprite.h"
#include "Music.h"

using namespace std;

class State {
private:
  Sprite background;
  Music music;
  bool quitRequested;

public:
  State();

  bool QuitRequested();
  void LoadAssets();
  void Update(float delta);
  void Render();
};
#endif
