#include "Game.h"
#include "Sprite.h"
#include "Camera.h"

#include <math.h>

Sprite::Sprite(GameObject& associated) : Component(associated) {
  this->texture = nullptr;
  this->scale = Vec2(1, 1);
  this->timeElapsed = 0;
  this->currentFrame = 0;
  this->frameTime = 1;
  this->frameCount = 1;
  this->associated.angleDeg = 0;
}

Sprite::Sprite(GameObject& associated, const char *file, int frameCount, float frameTime) : Component(associated) {
  this->texture = nullptr;
  this->scale = Vec2(1, 1);
  this->timeElapsed = 0;
  this->currentFrame = 0;
  this->frameTime = frameTime;
  frameCount == 0 ? this->frameCount = 1 : this->frameCount = frameCount;
  this->associated.angleDeg = 0;
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
    (int)(this->clipRect.w * this->scale.x),
    (int)(this->clipRect.h * this->scale.y)
  };

  if (
    SDL_RenderCopyEx(
      Game::GetInstance().GetRenderer(),
      this->texture,
      &(this->clipRect),
      &destineRect,
      this->associated.angleDeg,
      nullptr,
      SDL_FLIP_NONE
    ) != 0
  ) {
    printf("Couldn't render sprite!\n");
    printf("%s\n", SDL_GetError());
  }
}

void Sprite::UpdateBox() {
  Vec2 center = this->associated.box.GetCenter();
  this->associated.box.width = this->GetWidth();
  this->associated.box.height = this->GetHeight();
  this->associated.box.x = center.x - this->associated.box.width / 2;
  this->associated.box.y = center.y - this->associated.box.height / 2;
}

void Sprite::SetScaleX(float scaleX, float scaleY) {
  this->scale = Vec2(scaleX, scaleY);
  this->UpdateBox();
}

Vec2 Sprite::GetScale() {
  return(this->scale);
}

void Sprite::Open(const char *file) {
  this->texture = Resources::GetImage(file);

  if (this->texture != nullptr) {
    if (SDL_QueryTexture(this->texture, nullptr, nullptr, &(this->width), &(this->height)) != 0) {
      printf("Couldn't query texture!\n");
      printf("%s\n", SDL_GetError());
    }

    this->SetClip(0, 0, this->width / this->frameCount, this->height);

  } else {
    printf("Couldn't load texture!\n");
    printf("%s\n", SDL_GetError());
  }
}

void Sprite::SetClip(int x, int y, int width, int height) {
  this->clipRect = SDL_Rect {x, y, width, height};
}

int Sprite::GetWidth() {
  return(round(this->width / this->frameCount) * this->scale.x);
}

int Sprite::GetHeight() {
  return(this->height * this->scale.y);
}

bool Sprite::IsOpen() {
  if (this->texture != nullptr) {
    return(true);
  }
  else {
    return(false);
  }
}

void Sprite::SetFrame(int frame) {
  this->currentFrame = frame;
}

void Sprite::SetFrameCount(int frameCount) {
  this->frameCount = frameCount;
  this->currentFrame = 0;
  this->UpdateBox();
}

void Sprite::SetFrameTime(float frameTime) {
  this->frameTime = frameTime;
}

void Sprite::Start() {}

void Sprite::Update(float dt) {
  this->timeElapsed += dt;
  if(this->timeElapsed >= this->frameTime) {
    this->timeElapsed = 0;
    if(this->currentFrame >= (this->frameCount - 1)) {
      this->currentFrame = 0;
    } else {
      ++this->currentFrame;
    }
  }
    this->SetClip(
      this->currentFrame * (this->width / this->frameCount),
      this->clipRect.y,
      this->width / this->frameCount,
      this->clipRect.h
    );
}

bool Sprite::Is(const char *type) {
  if (strcmp(type, "Sprite") == 0) {
    return(true);
  } else {
    return(false);
  }
}
