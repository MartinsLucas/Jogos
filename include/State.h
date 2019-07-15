#ifndef STATE_H
#define STATE_H
#define INCLUDE_SDL

#include "SDL_include.h"

#include <iostream>
#include <memory>
#include <vector>

#include "Vec2.h"
#include "Sprite.h"
#include "Music.h"
#include "Sound.h"
#include "TileSet.h"
#include "TileMap.h"
#include "GameObject.h"
#include "InputManager.h"

using namespace std;

class State {
private:
  Music music;
  bool started;
  bool quitRequested;
  std::vector<std::shared_ptr<GameObject>> objectArray;

public:
  State();
  ~State();

  void Start();
  void Input();
  void Render();
  void LoadAssets();
  void LoadEnemies();
  void Update(float dt);

  bool QuitRequested();

  std::weak_ptr<GameObject> AddObject(GameObject *gameObject);
  std::weak_ptr<GameObject> GetObjectPtr(GameObject *gameObject);
};
#endif
