
#include "Vector2.h"

namespace Snake::Objects {

Vector2 Vector2::Zero = Vector2(0, 0);

Vector2::Vector2(float x, float y) : x(x), y(y) {};

Vector2::Vector2() : x(0), y(0) {};
} // namespace Snake::Objects
