#include "TileMap.h"
#include "Camera.h"

TileMap::TileMap(GameObject &associated, const char *file, TileSet *tileSet) : Component(associated) {
  this->Load(file);
  this->SetTileSet(tileSet);
}

void TileMap::Load(const char *file) {
  ifstream tileMap;
  tileMap.open(file);

  if(tileMap.good()) {
    char comma;

    tileMap >> this->mapWidth >> comma;
    tileMap >> this->mapHeight >> comma;
    tileMap >>  this->mapDepth >> comma;

    int currentValue = 0;

    for (int k = 0 ; k < this->mapDepth ; k++) {
      for (int j = 0 ; j < this->mapHeight ; j++) {
        for (int i = 0 ; i < this->mapWidth ; i++) {
          tileMap >> currentValue >> comma;
          this->tileMatrix.emplace_back(currentValue - 1);
        }
      }
    }
  } else {
    printf("Couldn't open TileMap file!\n");
  }
  tileMap.close();
}

void TileMap::SetTileSet(TileSet* tileSet) {
  this->tileSet = tileSet;
}

void TileMap::RenderLayer(int layer, int cameraX, int cameraY) {
  for (int j = 0 ; j < this->mapHeight ; j++) {
    for (int i = 0 ; i < this->mapWidth ; i++) {
      this->tileSet->RenderTile(
        this->At(i, j, layer),
        (this->tileSet->GetTileWidth() * i) - cameraX,
        (this->tileSet->GetTileHeight() * j) - cameraY
      );
    }
  }
}

void TileMap::Render() {
  for (int index = 0; index < this->mapDepth; index++) {
    RenderLayer(
      index,
      Camera::position.x * ( 1 + index * 1.5),
      Camera::position.y * ( 1 + index * 1.5)
    );
  }
}

int TileMap::GetDepth() {
  return(this->mapDepth);
}
int TileMap::GetWidth() {
  return(this->mapWidth);
}

int TileMap::GetHeight() {
  return(this->mapHeight);
}

int& TileMap::At(int i, int j, int k) {
  return(this->tileMatrix[i + (j * this->mapWidth) + (k * (this->mapWidth * this->mapHeight))]);
}

void TileMap::Update(float dt) {}

void TileMap::Start() {}

bool TileMap::Is(const char *type) {
  if (strcmp(type, "TileMap") == 0) {
    return(true);
  } else {
    return(false);
  }
}
