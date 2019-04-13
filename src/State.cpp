#include "State.h"

State::State() : background("assets/img/ocean.jpg"), music("assets/audio/stageState.ogg"){
  this->quitRequested = false;
  this->music.Play(-1);
}

bool State::QuitRequested() {
  return(this->quitRequested);
}

void State::Update(float delta) {
  if (SDL_QuitRequested()) {
    this->quitRequested = true;
  }
}

void State::LoadAssets() {
/*
  this->background("assets/img/ocean.jpg");
  this->music("assets/audio/stageState.ogg");
*/
}
void State::Render() {
  this->background.Render(0, 0);
}
