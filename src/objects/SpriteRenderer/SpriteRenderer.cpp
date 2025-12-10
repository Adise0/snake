#include "SpriteRenderer.h"
#include <algorithm>

namespace Snake::Objects {

std::vector<SpriteRenderer *> SpriteRenderer::spriteRenderers;

void SpriteRenderer::RegisterSpriteRenderer(SpriteRenderer *spriteRenderer) {
  // #region RegisterSpriteRenderer
  spriteRenderers.push_back(spriteRenderer);
  std::sort(spriteRenderers.begin(), spriteRenderers.end(),
            [](SpriteRenderer *a, SpriteRenderer *b) { return a->sortingLayer < b->sortingLayer; });
  // #endregion
}

void SpriteRenderer::UnregisterSpriteRenderer(SpriteRenderer *spriteRenderer) {

  auto foundRenderer = std::find(spriteRenderers.begin(), spriteRenderers.end(), spriteRenderer);
  if (foundRenderer != spriteRenderers.end()) spriteRenderers.erase(foundRenderer);
}


SpriteRenderer::SpriteRenderer(Vector2 position, Sprite *sprite)
    : position(position), sprite(sprite), render(true), sortingLayer(0) {
  RegisterSpriteRenderer(this);
};

SpriteRenderer::~SpriteRenderer() { UnregisterSpriteRenderer(this); }

} // namespace Snake::Objects
