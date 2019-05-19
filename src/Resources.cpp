#include "Game.h"
#include "Resources.h"

std::unordered_map<std::string, Mix_Music*> Resources::musicTable = std::unordered_map<std::string, Mix_Music*>();
std::unordered_map<std::string, Mix_Chunk*> Resources::soundTable = std::unordered_map<std::string, Mix_Chunk*>();
std::unordered_map<std::string, SDL_Texture*> Resources::imageTable = std::unordered_map<std::string, SDL_Texture*>();

void Resources::ClearMusics() {
  for(auto &music : Resources::musicTable) {
    if (music.second != nullptr) {
        Mix_FreeMusic(music.second);
    }
  }
  Resources::musicTable.clear();
}

void Resources::ClearSounds() {
  for(auto &chunk : Resources::soundTable) {
    if (chunk.second != nullptr) {
        Mix_FreeChunk(chunk.second);
    }
  }
  Resources::soundTable.clear();
}

void Resources::ClearImages() {
  for(auto &texture : Resources::imageTable) {
    if (texture.second != nullptr) {
      SDL_DestroyTexture(texture.second);
    }
  }
  Resources::imageTable.clear();
}

Mix_Music* Resources::GetMusic(const char* file) {
  if(Resources::musicTable.find(file) == Resources::musicTable.end()) {
    Mix_Music* music = Mix_LoadMUS(file);
    Resources::musicTable.emplace(file, music);
  }
  return(Resources::musicTable.at(file));
}

Mix_Chunk* Resources::GetSound(const char* file) {
  if(Resources::soundTable.find(file) == Resources::soundTable.end()) {
    Mix_Chunk* chunk = Mix_LoadWAV(file);
    Resources::soundTable.emplace(file, chunk);
  }
  return(Resources::soundTable.at(file));
}

SDL_Texture* Resources::GetImage(const char* file) {
  if(Resources::imageTable.find(file) == Resources::imageTable.end()) {
    SDL_Texture* texture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), file);
    Resources::imageTable.emplace(file, texture);
  }
  return(Resources::imageTable.at(file));
}
