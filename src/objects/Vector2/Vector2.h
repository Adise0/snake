#pragma once

namespace Snake::Objects {
struct Vector2 {
public:
  /// @brief Vector2 with x and y set to 0
  static Vector2 Zero;

public:
  /// @brief The x coordenate
  float x;
  /// @brief The y coordenate
  float y;

  /// @brief Creates a new Vector2
  /// @param x The X coordenate
  /// @param y The Y coordenate
  Vector2(float x, float y);
  Vector2();
};
} // namespace Snake::Objects
