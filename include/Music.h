#ifndef MUSIC_H
#define MUSIC_H

#include <iostream>

#define INCLUDE_SDL_MIXER
#include "SDL_include.h"

using namespace std;

class Music {
private:
  Mix_Music *music;
public:
  Music();
  Music(const char *file);

  ~Music();

  void Play(int times = -1);
  void Stop(int msToStop = 1500);
  void Open(const char *file);
  bool IsOpen();
};
#endif
