#include "TileSet.h"

TileSet::TileSet(int tileWidth, int tileHeight, const char *file) : tileSet(*new GameObject(), file) {
    this->tileWidth = tileWidth;
    this->tileHeight = tileHeight;

    if (this->tileSet.IsOpen()) {
      this->columns = this->tileSet.GetWidth() / this->tileWidth;
      this->rows = this->tileSet.GetHeight() / this->tileHeight;
    } else {
      printf("Couldn't load TileSet!\n");
    }
}

void TileSet::RenderTile(unsigned index, float xPosition, float yPosition) {
  if (index < (this->rows * this->columns)) {
    this->tileSet.SetClip(
      (this->tileWidth * this->GetTileColumn(index)),
      (this->tileHeight * this->GetTileRow(index)),
      this->tileWidth,
      this->tileHeight
    );
    this->tileSet.Render(xPosition, yPosition);
  }
}

int TileSet::GetTileRow(unsigned index) {
  return(index / this->columns);
}
int TileSet::GetTileColumn(unsigned index) {
  return(index % this->columns);
}

int TileSet::GetTileWidth() {
  return(this->tileWidth);
}

int TileSet::GetTileHeight() {
  return(this->tileHeight);
}
