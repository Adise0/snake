#pragma once
#include "../Sprite/Sprite.h"
#include "../Vector2/Vector2.h"


namespace Snake::Objects {
class SpriteRenderer {
public:
  /// @brief The positioon in the screen
  Vector2 position;
  /// @brief The sprite to render
  Sprite *sprite;


  /// @brief Creates a new SpriteRenderer
  /// @param position The position in the screen
  /// @param sprite The initial sprite
  SpriteRenderer(Vector2 position, Sprite *sprite);
};
} // namespace Snake::Objects
