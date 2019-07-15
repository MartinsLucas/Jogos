#include "State.h"
#include "Alien.h"
#include "Camera.h"
#include "CameraFollower.h"

#include <memory>

State::State() : music("assets/audio/stageState.ogg") {
  this->quitRequested = false;
  this->started = false;
  // this->music.Play(-1);

  this->objectArray = std::vector<std::shared_ptr<GameObject>>();
}

void State::LoadEnemies() {
  GameObject *alienGameObject = new GameObject();
  alienGameObject->AddComponent(new Alien(*alienGameObject, 0));

  alienGameObject->box.SetCenter(Vec2(512.0, 300.0));

  this->AddObject(alienGameObject);

  Camera::Follow(alienGameObject);
}

void State::Start() {
  this->LoadAssets();
  this->LoadEnemies();
  for(auto &object : this->objectArray) {
    object->Start();
  }
  this->started = true;
}

State::~State() {
  for (int index = this->objectArray.size() - 1 ; index >= 0 ; --index) {
    delete this->objectArray[index].get();
  }
  this->objectArray.clear();
}

void State::Render() {
  for(auto &object : this->objectArray) {
    object->Render();
  }
}

void State::LoadAssets() {
  GameObject *spriteObject = new GameObject();
  Sprite *backgroundSprite = new Sprite(*spriteObject, "assets/img/ocean.jpg");
  CameraFollower *background = new CameraFollower(*spriteObject);

  spriteObject->box.x = 0;
  spriteObject->box.y = 0;
  spriteObject->box.width = backgroundSprite->GetWidth();
  spriteObject->box.height = backgroundSprite->GetHeight();

  spriteObject->AddComponent(backgroundSprite);
  spriteObject->AddComponent(background);
  this->AddObject(spriteObject);

  GameObject *tileMapObject = new GameObject();
  TileSet *tileSet = new TileSet(64, 64, "assets/img/tileset.png");

  TileMap *tileMap = new TileMap(*tileMapObject, "assets/map/tileMap.txt", tileSet);

  tileMapObject->box.x = 0;
  tileMapObject->box.y = 0;

  tileMapObject->AddComponent(tileMap);
  this->AddObject(tileMapObject);
}

void State::Update(float dt) {
  if(
    InputManager::GetInstance().QuitRequested() ||
    InputManager::GetInstance().KeyPress(ESCAPE_KEY)
  ) {
    this->quitRequested = true;
  }

  Camera::Update(dt);

  for(auto &object : this->objectArray) {
    object->Update(dt);
  }

  for(unsigned int index = 0 ; (index < this->objectArray.size()) ; index++) {
    if (this->objectArray[index].get()->IsDead()) {
      this->objectArray.erase(this->objectArray.begin() + index);
    }
  }
}

std::weak_ptr<GameObject> State::AddObject(GameObject *gameObject) {
  std::shared_ptr<GameObject> sharedGameObject = std::shared_ptr<GameObject>(gameObject);
  this->objectArray.push_back(sharedGameObject);
  if (this->started) {
    sharedGameObject->Start();
  }
  return(std::weak_ptr<GameObject>(sharedGameObject));
}

std::weak_ptr<GameObject> State::GetObjectPtr(GameObject *gameObject) {
  std::weak_ptr<GameObject> weakGameObject = std::weak_ptr<GameObject>();
  std::shared_ptr<GameObject> sharedGameObject = std::shared_ptr<GameObject>(gameObject);
  for(auto &object : this->objectArray) {
    if(&object == &sharedGameObject) {
      weakGameObject = std::weak_ptr<GameObject>(sharedGameObject);
    }
  }
  return(weakGameObject);
}

bool State::QuitRequested() {
  return(this->quitRequested);
}
