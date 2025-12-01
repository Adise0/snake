#include "SpriteRenderer.h"

namespace Snake::Objects {

vector<SpriteRenderer *> SpriteRenderer::spriteRenderers;

void SpriteRenderer::RegisterSpriteRenderer(SpriteRenderer *spriteRenderer) {
  // #region RegisterSpriteRenderer
  spriteRenderers.push_back(spriteRenderer);
  // #endregion
}

} // namespace Snake::Objects
