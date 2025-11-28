#include "Renderables.h"
#include "../Sprites/Sprites.h"

using namespace Snake::Objects;
namespace Snake {
namespace Data {
// Renderable Renderables::testRenderable(Sprites::testSprite);
// Renderable Renderables::testRenderable;
// Renderable &Renderables::testRenderable = Renderable(Vector2::Zero, Sprites::testSprite);

// Renderable &Renderables::testRenderable() {
//   static Renderable r(Vector2(0, 10), Sprites::testSprite());
//   return r;
// }

Renderable Renderables::snakeHead(Vector2(0, 10), Sprites::head_right);
} // namespace Data

} // namespace Snake
