#pragma once

namespace Snake::Objects {
struct Vector2 {
public:
  /// @brief The x coordenate
  float x;
  /// @brief The y coordenate
  float y;

  /// @brief Creates a new Vector2
  /// @param x The X coordenate
  /// @param y The Y coordenate
  Vector2(float x, float y);
  ;
};
} // namespace Snake::Objects
