#include "Sprite.h"


namespace Snake::Objects {
int Sprite::idStore = 0;

Sprite::Sprite(std::vector<std::u32string> characters)
    : id(GetNewId()), rect(GetRect(characters)), characters(characters) {
  IsSpriteValid(characters);
}


bool Sprite::IsSpriteValid(std::vector<std::u32string> characters) {
  short width = characters[0].length();

  for (std::u32string line : characters) {
    if (line.length() != width) throw new std::exception("Invalid sprite");
  }
  return true;
}

Vector2 Sprite::GetRect(std::vector<std::u32string> characters) {
  return Vector2(characters[0].length(), characters.size());
}

int Sprite::GetNewId() {
  idStore++;
  return idStore;
}
} // namespace Snake::Objects
