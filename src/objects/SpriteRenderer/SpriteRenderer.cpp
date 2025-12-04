#include "SpriteRenderer.h"

namespace Snake::Objects {

std::vector<SpriteRenderer *> SpriteRenderer::spriteRenderers;

void SpriteRenderer::RegisterSpriteRenderer(SpriteRenderer *spriteRenderer) {
  // #region RegisterSpriteRenderer
  spriteRenderers.push_back(spriteRenderer);
  // #endregion
}

void SpriteRenderer::UnregisterSpriteRenderer(SpriteRenderer *spriteRenderer) {

  auto foundRenderer = std::find(spriteRenderers.begin(), spriteRenderers.end(), spriteRenderer);
  if (foundRenderer != spriteRenderers.end()) spriteRenderers.erase(foundRenderer);
}


SpriteRenderer::SpriteRenderer(Vector2 position, Sprite *sprite)
    : position(position), sprite(sprite), render(true) {
  RegisterSpriteRenderer(this);
};

SpriteRenderer::~SpriteRenderer() { UnregisterSpriteRenderer(this); }

} // namespace Snake::Objects
