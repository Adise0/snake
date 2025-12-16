#include "Sprites.h"
#include <string>

namespace Snake::Data {

Sprite Sprites::appleSprite = Sprite(std::vector<std::u32string>{
    U"   ,   ",
    U" /-v-\\ ",
    U" \\_^_/ ",
});

} // namespace Snake::Data


