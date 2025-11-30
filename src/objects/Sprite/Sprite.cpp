#include "Sprite.h"


namespace Snake::Objects {
int Sprite::idStore = 0;

Sprite::Sprite(vector<u32string> characters)
    : id(GetNewId()), rect(GetRect(characters)), characters(characters) {
  IsSpriteValid(characters);
}



bool Sprite::IsSpriteValid(vector<u32string> characters) {
  short width = characters[0].length();

  for (u32string line : characters) {
    if (line.length() != width) throw new exception("Invalid sprite");
  }
  return true;
}

Vector2 Sprite::GetRect(vector<u32string> characters) {
  return Vector2(characters[0].length(), characters.size());
}

int Sprite::GetNewId() {
  idStore++;
  return idStore;
}
} // namespace Snake::Objects
