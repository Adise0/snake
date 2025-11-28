#include "Sprites.h"
#include <string>
#include <vector>


namespace Snake {
namespace Data {

Sprite Sprites::head_right = Sprite(0, {U"(.)\\   ", U"---bb)", U"(.)/   "});
Sprite Sprites::head_left = Sprite(1, {U"   /(.)", U"(bb---", U"   \\(.)"});
Sprite Sprites::head_up = Sprite(2, {U"   <()", U"<(####", U"   <()"});
Sprite Sprites::head_down = Sprite(3, {U"   <()", U"<(####", U"   <()"});

} // namespace Data

} // namespace Snake
