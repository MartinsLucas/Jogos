#include "Music.h"

Music::Music() {
  this->music = nullptr;
}
Music::Music(const char *file) {
  this->music = nullptr;
  this->Open(file);
}

Music::~Music() {
  this->Stop();
}

void Music::Play(int times) {
  if (this->music != nullptr) {
    Mix_PlayMusic(this->music, times);
  }
}

void Music::Stop(int msToStop) {
  Mix_FadeOutMusic(msToStop);
}

void Music::Open(const char *file) {
  this->music = Resources::GetMusic(file);

  if (this->music == nullptr) {
    printf("Couldn't load music!\n");
    printf("%s\n", SDL_GetError());
  }
}

bool Music::IsOpen() {
  if (this->music != nullptr) {
    return(true);
  }
  else {
    return(false);
  }
}
