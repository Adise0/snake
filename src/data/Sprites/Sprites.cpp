#include "Sprites.h"
#include <string>

namespace Snake::Data {

Sprite Sprites::head_right = Sprite(std::vector<std::u32string>{U"(.)\\  ", U"---bb>", U"(.)/  "});
Sprite Sprites::square = Sprite(std::vector<std::u32string>{U"    ", U" ###", U"    "});
Sprite Sprites::apple = Sprite(std::vector<std::u32string>{U"  ´  ", U" ^-^ ", U" \\_ / "});
} // namespace Snake::Data


