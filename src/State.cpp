#include "State.h"
#include "Camera.h"

State::State() : music("assets/audio/stageState.ogg") {
  this->quitRequested = false;
  this->music.Play(-1);

  this->objectArray = std::vector<std::shared_ptr<GameObject>>();

  this->LoadAssets();
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
  Sprite *background = new Sprite(*spriteObject, "assets/img/ocean.jpg");

  spriteObject->box.x = 0;
  spriteObject->box.y = 0;
  spriteObject->box.width = background->GetWidth();
  spriteObject->box.height = background->GetHeight();

  spriteObject->AddComponent(background);
  this->objectArray.emplace_back(spriteObject);

  GameObject *tileMapObject = new GameObject();
  TileSet *tileSet = new TileSet(64, 64, "assets/img/tileset.png");

  TileMap *tileMap = new TileMap(*tileMapObject, "assets/map/tileMap.txt", tileSet);

  tileMapObject->box.x = 0;
  tileMapObject->box.y = 0;

  tileMapObject->AddComponent(tileMap);
  this->objectArray.emplace_back(tileMapObject);
}

void State::Update(float dt) {
  if(
    InputManager::GetInstance().QuitRequested() ||
    InputManager::GetInstance().KeyPress(ESCAPE_KEY)
  ) {
    this->quitRequested = true;
  }

  Camera::Update(dt);

  if(InputManager::GetInstance().KeyPress(SPACE_BAR)) {
    Vec2 objectPosition = Vec2(
      InputManager::GetInstance().GetMouseX() + Camera::position.x,
      InputManager::GetInstance().GetMouseY() + Camera::position.y
    ).RandomRotation( 200 );
    AddObject((int)objectPosition.x, (int)objectPosition.y);
  }

  for(auto &object : this->objectArray) {
    object->Update(dt);
  }
  for(unsigned int index = 0 ; (index < this->objectArray.size()) ; index++) {
    if (this->objectArray[index].get()->IsDead()) {
      this->objectArray.erase(this->objectArray.begin() + index);
    }
  }
}

void State::AddObject(int mouseX, int mouseY) {
  GameObject *object = new GameObject();
  Sprite *sprite = new Sprite(*object, "assets/img/penguinface.png");
  Sound *sound = new Sound(*object, "assets/audio/boom.wav");
  Face *face = new Face(*object);

  object->box.width = sprite->GetWidth();
  object->box.height = sprite->GetHeight();
  object->box.x = mouseX - (sprite->GetWidth() / 2);
  object->box.y = mouseY - (sprite->GetHeight() / 2);

  object->AddComponent(sprite);
  object->AddComponent(sound);
  object->AddComponent(face);

  this->objectArray.emplace_back(object);
}

bool State::QuitRequested() {
  return(this->quitRequested);
}
