#include "Renderables.h"
#include "../Sprites/Sprites.h"

using namespace Snake::Objects;
namespace Snake {
namespace Data {
// Renderable Renderables::testRenderable(Sprites::testSprite);
// Renderable Renderables::testRenderable;
// Renderable &Renderables::testRenderable = Renderable(Vector2::Zero, Sprites::testSprite);

Renderable &Renderables::testRenderable() {
  static Renderable r(Vector2(0, 15), Sprites::testSprite());
  return r;
}
} // namespace Data

} // namespace Snake
