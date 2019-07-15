#include "Game.h"
#include "Sprite.h"
#include "Camera.h"

Sprite::Sprite(GameObject& associated) : Component(associated) {
  this->texture = nullptr;
}

Sprite::Sprite(GameObject& associated, const char *file) : Component(associated) {
  this->texture = nullptr;
  this->Open(file);
}

void Sprite::Render() {
  this->Render(
    this->associated.box.x - Camera::position.x,
    this->associated.box.y - Camera::position.y
  );
}

void Sprite::Render(int xPosition, int yPosition) {
  SDL_Rect destineRect = SDL_Rect {
    xPosition,
    yPosition,
    this->clipRect.w,
    this->clipRect.h
  };

  if (
    SDL_RenderCopy(
      Game::GetInstance().GetRenderer(),
      this->texture,
      &(this->clipRect),
      &destineRect
    ) != 0
  ) {
    printf("Couldn't render sprite!\n");
    printf("%s\n", SDL_GetError());
  }
}

void Sprite::Update(float dt) {}

void Sprite::Open(const char *file) {
  this->texture = Resources::GetImage(file);

  if (this->texture != nullptr) {
    if (SDL_QueryTexture(this->texture, nullptr, nullptr, &(this->width), &(this->height)) != 0) {
      printf("Couldn't query texture!\n");
      printf("%s\n", SDL_GetError());
    }

    this->SetClip(0, 0, this->width, this->height);

  } else {
    printf("Couldn't load texture!\n");
    printf("%s\n", SDL_GetError());
  }
}

void Sprite::SetClip(int x, int y, int width, int height) {
  this->clipRect = SDL_Rect {x, y, width, height};
}

int Sprite::GetWidth() {
  return(this->width);
}

int Sprite::GetHeight() {
  return(this->height);
}

bool Sprite::IsOpen() {
  if (this->texture != nullptr) {
    return(true);
  }
  else {
    return(false);
  }
}

bool Sprite::Is(const char *type) {
  if (strcmp(type, "Sprite") == 0) {
    return(true);
  } else {
    return(false);
  }
}
