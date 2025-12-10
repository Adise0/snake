#pragma once

namespace Snake::Objects {
struct Vector2 {
public:
  /// @brief Vector2 with x and y set to 0
  static Vector2 Zero;
  static Vector2 Right;
  static Vector2 Left;
  static Vector2 Up;
  static Vector2 Down;

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
  /// @brief Inverses the vector
  /// @return The inverse vector
  Vector2 Inverse() const { return Vector2(-x, -y); }
  Vector2 ToInts() const { return Vector2((int)x, (int)y); }

  Vector2 operator*(const float num) const { return Vector2(x * num, y * num); }
  Vector2 operator*(const Vector2 &other) const { return Vector2(x * other.x, y * other.y); }
  Vector2 &operator*=(const float num) {
    x *= num;
    y *= num;
    return *this;
  }

  Vector2 operator/(const Vector2 &other) const { return Vector2(x / other.x, y / other.y); }

  Vector2 operator+(const Vector2 &other) const { return Vector2(x + other.x, y + other.y); }
  Vector2 &operator+=(const Vector2 &other) {
    x += other.x;
    y += other.y;
    return *this;
  }

  Vector2 operator-(const Vector2 &other) const { return Vector2(x - other.x, y - other.y); }
  bool operator==(const Vector2 &other) const { return x == other.x && y == other.y; }
  bool operator!=(const Vector2 &other) const { return !(*this == other); }
};
} // namespace Snake::Objects
