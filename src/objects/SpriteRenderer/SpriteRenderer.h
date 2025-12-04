#pragma once
#include "../Sprite/Sprite.h"
#include "../Vector2/Vector2.h"


namespace Snake::Objects {
class SpriteRenderer {
public:
  /// @brief The store of all sprite renderers
  static std::vector<SpriteRenderer *> spriteRenderers;
  /// @brief Registers the given sprite into the global store
  /// @param spriteRenderer The sprite renderer to register
  void RegisterSpriteRenderer(SpriteRenderer *spriteRenderer);

  /// @brief Unregisters the given sprite from the global store
  /// @param spriteRenderer The sprite renderer to unregister
  void UnregisterSpriteRenderer(SpriteRenderer *spriteRenderer);


public:
  /// @brief The positioon in the screen
  Vector2 position;
  /// @brief The sprite to render
  Sprite *sprite;
  /// @brief Whether this renderer should be rendered
  bool render;

  /// @brief Creates a new SpriteRenderer
  /// @param position The position in the screen
  /// @param sprite The initial sprite
  SpriteRenderer(Vector2 position, Sprite *sprite);
  ~SpriteRenderer();
};
} // namespace Snake::Objects
