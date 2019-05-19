#ifndef TILE_SET_H
#define TILE_SET_H

#include <iostream>

#include "Sprite.h"
#include "GameObject.h"

using namespace std;

class TileSet {
private:
  int tileWidth;
  int tileHeight;
  Sprite tileSet;
  unsigned rows;
  unsigned columns;

public:
  TileSet(GameObject &spriteObject, int tileWidth, int tileHeight, const char *file);

  void RenderTile(unsigned index, float xPosition, float yPosition);
  int GetTileWidth();
  int GetTileHeight();
  int GetTileRow(unsigned index);
  int GetTileColumn(unsigned index);
};
#endif
