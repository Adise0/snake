
#include "Vector2.h"

namespace Snake::Objects {

Vector2 Vector2::Zero = Vector2(0, 0);
Vector2 Vector2::Right = Vector2(1, 0);
Vector2 Vector2::Left = Vector2(-1, 0);
Vector2 Vector2::Up = Vector2(0, -1);
Vector2 Vector2::Down = Vector2(0, 1);

Vector2::Vector2(float x, float y) : x(x), y(y) {};
Vector2::Vector2() : x(0), y(0) {};


} // namespace Snake::Objects
