#pragma once
#include "../Vector2/Vector2.h"
#include <string>
#include <vector>


using namespace std;

namespace Snake::Objects {

class Sprite {
private:
  /// @brief The static id counter
  static int idStore;

  /// @brief Gets a new safew id
  /// @return The id to use
  static int GetNewId();


  /// @brief Gets the srpite rect
  /// @return The sprite rect
  static Vector2 GetRect(vector<u32string> characters);


  /// @brief Checks if the sprite is valid
  /// @return Whether the sprite is valid
  static bool IsSpriteValid(vector<u32string> characters);

private:
  /// @brief The id of the sprite
  int id;

public:
  /// @brief The rect (size) of the sprite
  Vector2 rect;
  /// @brief The characters of the sprite
  vector<u32string> characters;

  /// @brief Creates a new sprite
  /// @param characters The characters of the sprite
  Sprite(vector<u32string> characters);
};
} // namespace Snake::Objects
