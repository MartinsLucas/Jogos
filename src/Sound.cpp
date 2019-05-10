#include "Sound.h"

Sound::Sound(GameObject &associated) : Component(associated) {
  this->channel = -1;
  this->chunk = nullptr;
}

Sound::Sound(GameObject &associated, const char* file) : Sound(associated){
  this->Open(file);
}

Sound::~Sound() {
  if(!Mix_Playing(this->channel)) {
    this->Stop();
    if(this->chunk != nullptr) {
      Mix_FreeChunk(this->chunk);
    } else {
      printf("Can not free an unnexistant sound chunk!\n");
    }
  }
}

void Sound::Stop(){
  if(!Mix_Playing(this->channel)) {
    if(this->chunk != nullptr) {
      Mix_HaltChannel(this->channel);
    } else {
      printf("There's no sound allocate yet!\n");
    }
  }
}

void Sound::Render() {}

void Sound::Update(float delta) {}

void Sound::Play(int times){
  int newChannel = Mix_PlayChannel(this->channel, this->chunk, (times - 1));
  if(newChannel >= 0) {
    this->channel = newChannel;
  } else {
    printf("Channel could not be played!\n");
    printf("%s\n", Mix_GetError());
  }
}

void Sound::Open(const char *file) {
  this->chunk = Mix_LoadWAV(file);

  if(this->chunk == nullptr) {
    printf("Sound could not be loaded!\n");
    printf("%s\n", Mix_GetError());
  }
}

bool Sound::IsOpen() {
  if (this->chunk != nullptr) {
    return(true);
  }
  else {
    return(false);
  }
}

bool Sound::Is(const char *type) {
  if (strcmp(type, "Sound") == 0) {
    return(true);
  } else {
    return(false);
  }
}
