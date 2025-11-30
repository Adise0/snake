#pragma once
#include <string>
#include <vector>


using namespace std;

namespace Snake::Objects {

class Sprite {
private:
  /// @brief The id of the sprite
  int id;

public:
  /// @brief The characters of the sprite
  vector<u32string> characters;
  /// @brief Creates a new sprite
  /// @param characters The characters of the sprite
  Sprite(vector<u32string> characters);

private:
  /// @brief The static id counter
  static int idStore;

  /// @brief Gets a new safew id
  /// @return The id to use
  static int GetNewId();
};
} // namespace Snake::Objects
