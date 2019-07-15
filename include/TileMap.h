#ifndef TILE_MAP_H
#define TILE_MAP_H

#include <iostream>
#include <fstream>

#include "Component.h"
#include "TileSet.h"
#include "GameObject.h"

using namespace std;

class TileMap : public Component {
private:
  int mapDepth;
  int mapWidth;
  int mapHeight;
  TileSet* tileSet;
  std::vector<int> tileMatrix;

public:
  TileMap(GameObject &associated, const char *file, TileSet *tileSet);

  void Render();
  void Update(float delta = 0);
  void Load(const char *file);
  void SetTileSet(TileSet *tileSet);
  void RenderLayer(int layer, int cameraX = 0, int cameraY = 0);
  int GetDepth();
  int GetWidth();
  int GetHeight();
  int& At(int i, int j, int k = 0);
  bool Is(const char *type);

};
#endif
