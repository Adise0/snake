#include "Renderable.h"
#include "iostream"

namespace Snake {
namespace Objects {
Renderable::Renderable(Vector2 position, Sprite &sprite) : position(position), sprite(sprite) {};
} // namespace Objects
} // namespace Snake
