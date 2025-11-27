#include "Sprites.h"
#include <string>
#include <vector>


namespace Snake {
namespace Data {

Sprite &Sprites::testSprite() {
  static Sprite s({U"    ::::    ", U"::::::::::::", U"    ::::    "});
  return s;
}

} // namespace Data

} // namespace Snake
