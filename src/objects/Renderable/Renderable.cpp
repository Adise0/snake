#include "Renderable.h"
#include "iostream"

namespace Snake {
namespace Objects {

// Renderable::Renderable(string t) { cout << t; };
// Renderable::Renderable(Vector2 position, Sprite sprite) : position(Vector2::Zero), sprite(sprite) {}

Renderable::Renderable(Vector2 position, Sprite &sprite) : position(position), sprite(sprite) {};
// Renderable::
} // namespace Objects
} // namespace Snake
