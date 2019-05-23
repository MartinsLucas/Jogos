#include "InputManager.h"


InputManager::InputManager() {
  this->mouseX = 0;
  this->mouseY = 0;

  this->mouseState[6] = {0};
  this->mouseUpdate[6] = {0};

  this->updateCounter = 0;
  this->quitRequested = false;
}

InputManager::~InputManager() {}

void InputManager::Update() {
  this->updateCounter++;

	SDL_GetMouseState(&this->mouseX, &this->mouseY);

  for (size_t i = 0; i < 6; i++) {
    printf("Mouse State: %s\nMouse Update:%d\n", (mouseState[i] ? "True" : "False"), mouseUpdate[i]);
  }

  SDL_Event event;
	while(SDL_PollEvent(&event)) {

		if(event.type == SDL_QUIT) {
			this->quitRequested = true;
		}

    if(event.type == SDL_MOUSEBUTTONDOWN) {
      this->mouseState[event.button.button] = true;
      this->mouseUpdate[event.button.button] = this->updateCounter;
    }
    if(event.type == SDL_MOUSEBUTTONUP) {
      this->mouseState[event.button.button] = false;
      this->mouseUpdate[event.button.button] = this->updateCounter;
    }
    if( event.type == SDL_KEYDOWN ) {
      if(event.key.repeat == 0) {
        this->keyState[event.key.keysym.sym] = true;
        this->keyUpdate[event.key.keysym.sym] = this->updateCounter;
      }
    }
    if(event.type == SDL_KEYUP) {
      this->keyState[event.key.keysym.sym] = false;
      this->keyUpdate[event.key.keysym.sym] = this->updateCounter;
    }
	}
}

int InputManager::GetMouseX() {
  return(this->mouseX);
}
int InputManager::GetMouseY() {
  return(this->mouseY);
}

bool InputManager::KeyPress(int key) {
  return(this->keyState[key] && this->keyUpdate[key] == this->updateCounter ? true : false);
}
bool InputManager::KeyRelease(int key) {
  return((!this->keyState[key]) && this->keyUpdate[key] == this->updateCounter ? true : false);
}
bool InputManager::IsKeyDown(int key) {
  return(this->keyState[key]);
}

bool InputManager::MousePress(int button) {
  return(this->mouseState[button] && this->mouseUpdate[button] == this->updateCounter ? true : false);
}

bool InputManager::MouseRelease(int button) {
  return((!this->mouseState[button]) && this->mouseUpdate[button] == this->updateCounter ? true : false);
}

bool InputManager::IsMouseDown(int button) {
  return(this->mouseState[button]);
}

bool InputManager::QuitRequested() {
  return(this->quitRequested);
}

InputManager& InputManager::GetInstance() {
  static InputManager instance;
  return(instance);
}
