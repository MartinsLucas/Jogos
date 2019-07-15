#define INCLUDE_SDL
#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER

#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 600

#include "SDL_include.h"

#include "Game.h"
#include "State.h"
#include "Resources.h"
#include "InputManager.h"

#include <cstdlib>
#include <ctime>

Game *Game::instance = nullptr;
int Game::screenWidth = SCREEN_WIDTH;
int Game::screenHeight = SCREEN_HEIGHT;

Game::Game(const char *title, int width, int height) {
  srand( (unsigned) time(NULL) );

  if (Game::instance == nullptr) {
    Game::instance = this;
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER) == 0) {
      if (IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF) != 0) {
        Mix_Init(MIX_INIT_OGG | MIX_INIT_MP3);
        if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == 0) {
          Mix_AllocateChannels(32);

          this->window = SDL_CreateWindow(
            title,
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            width,
            height,
            0
          );
          if (this->window != nullptr) {
            this->renderer = SDL_CreateRenderer(
              this->window,
              -1,
              SDL_RENDERER_ACCELERATED
            );
            if (this->renderer != nullptr) {
              this->state = new State();
              this->dt = 0;
              this->frameStart = 0;
            } else {
              printf("SDL_renderer couldn't be created!\n");
              printf("%s\n", SDL_GetError());
            }
          } else {
            printf("SDL_window couldn't be created!\n");
            printf("%s\n", SDL_GetError());
          }
        } else {
          printf("SDL_mixer couldn't be initialized!\n");
          printf("%s\n", SDL_GetError());
        }
      } else {
        printf("SDL_image couldn't be initialized!\n");
        printf("%s\n", SDL_GetError());
      }
    } else {
      printf("SDL couldn't be initialized!\n");
      printf("%s\n", SDL_GetError());
    }
  } else {
    printf("An instance of the Game Engine is already running!\n");
  }
}

Game::~Game() {
  SDL_DestroyRenderer(this->renderer);
  SDL_DestroyWindow(this->window);
  Mix_CloseAudio();
  Mix_Quit();
  IMG_Quit();
  SDL_Quit();
}

SDL_Renderer* Game::GetRenderer() {
  return(this->renderer);
}

State& Game::GetState() {
  return(*(this->state));
}

Game& Game::GetInstance() {
  if (Game::instance == nullptr) {
    Game::instance = new Game("Lucas de Araujo Martins - 150015771", Game::screenWidth, Game::screenHeight);
  }
  return(*instance);
}

void Game::Run() {
  while (this->state->QuitRequested() != true) {
    this->CalculateDeltaTime();
    InputManager::GetInstance().Update();
    this->state->Update(this->dt);
    this->state->Render();
    SDL_RenderPresent(this->GetRenderer());
    SDL_Delay(33);
  }
  Resources::ClearImages();
}

void Game::CalculateDeltaTime() {
  int sdlTicks = SDL_GetTicks();
  this->dt = (sdlTicks - this->frameStart) / 1000.0;
  this->frameStart = sdlTicks;
}

float Game::GetDeltaTime() {
  return(this->dt);
}

int Game::GetScreenWidth() {
  return(Game::screenWidth);
}
int Game::GetScreenHeight() {
  return(Game::screenHeight);
}
