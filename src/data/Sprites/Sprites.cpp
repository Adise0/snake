#include "Sprites.h"
#include <string>
#include <vector>


namespace Snake {
namespace Data {

Sprite Sprites::head_right = Sprite({U"()>   ", U"####)>", U"()>   "});
Sprite Sprites::head_left = Sprite({U"   <()", U"<(####", U"   <()"});
Sprite Sprites::head_up = Sprite({U"   <()", U"<(####", U"   <()"});
Sprite Sprites::head_down = Sprite({U"   <()", U"<(####", U"   <()"});

} // namespace Data

} // namespace Snake
