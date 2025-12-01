#include "SpriteRenderer.h"

namespace Snake::Objects {

std::vector<SpriteRenderer *> SpriteRenderer::spriteRenderers;

void SpriteRenderer::RegisterSpriteRenderer(SpriteRenderer *spriteRenderer) {
  // #region RegisterSpriteRenderer
  spriteRenderers.push_back(spriteRenderer);
  // #endregion
}


SpriteRenderer::SpriteRenderer(Vector2 position, Sprite *sprite)
    : position(position), sprite(sprite) {
  RegisterSpriteRenderer(this);
};

} // namespace Snake::Objects
