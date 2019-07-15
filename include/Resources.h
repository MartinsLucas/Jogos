#ifndef RESOURCES_H
#define RESOURCES_H

#define ASSETS_PATH "assets/"

#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER
#include "SDL_include.h"

#include <iostream>
#include <unordered_map>

using namespace std;

class Resources {
private:
  static std::unordered_map<std::string, Mix_Music*> musicTable;
  static std::unordered_map<std::string, Mix_Chunk*> soundTable;
  static std::unordered_map<std::string, SDL_Texture*> imageTable;
public:
  static void ClearMusics();
  static void ClearSounds();
  static void ClearImages();
  static Mix_Music* GetMusic(const char* file);
  static Mix_Chunk* GetSound(const char* file);
  static SDL_Texture* GetImage(const char* file);
};
#endif
