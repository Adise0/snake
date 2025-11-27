#pragma once
#include "../../rendering/Sprite/Sprite.h"
#include "../Vector2/Vector2.h"

using namespace Snake::Rendering;

namespace Snake {
namespace Objects {
class Renderable {
public:
  Vector2 position;
  Sprite sprite;

  Renderable(Vector2 position, Sprite sprite);
};
} // namespace Objects
} // namespace Snake
