#include "Sprite.h"


namespace Snake::Objects {
int Sprite::idStore = 0;

Sprite::Sprite(vector<u32string> characters) {
  this->id = GetNewId();
  this->characters = characters;
}

int Sprite::GetNewId() {
  idStore++;
  return idStore;
}
} // namespace Snake::Objects
