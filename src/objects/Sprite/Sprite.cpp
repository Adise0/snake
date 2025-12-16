#include "Sprite.h"


namespace Snake::Objects {
int Sprite::idStore = 0;

Sprite::Sprite(std::vector<std::u32string> characters)
    : id(GetNewId()), rect(GetRect(characters)), characters(characters) {
  IsSpriteValid(characters);
}

bool Sprite::IsSpriteValid(std::vector<std::u32string> characters) {
  // #region IsSpriteValid
  short width = characters[0].length();

  for (std::u32string line : characters) {
    if (line.length() != width) throw new std::exception("Invalid sprite");
  }
  return true;
  // #endregion
}

Vector2 Sprite::GetRect(std::vector<std::u32string> characters) {
  // #region GetRect
  return Vector2(characters[0].length(), characters.size());
  // #endregion
}

int Sprite::GetNewId() {
  // #region GetNewId
  idStore++;
  return idStore;
  // #endregion
}
} // namespace Snake::Objects
