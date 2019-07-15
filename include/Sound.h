#ifndef SOUND_H
#define SOUND_H
#define INCLUDE_SDL_MIXER

#include "SDL_include.h"

#include <iostream>

#include "Component.h"
#include "Resources.h"

using namespace std;

class Sound : public Component {
private:
  int channel;
  Mix_Chunk *chunk;

public:
  Sound(GameObject &associated);
  Sound(GameObject &associated, const char* file);
  ~Sound();

  void Stop();
  void Render();
  void Update(float dt);
  void Play(int times = 1);
  void Open(const char *file);
  bool IsOpen();
  bool Is(const char *type);
  bool CanStop();
};
#endif
