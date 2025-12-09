#include "Sprites.h"
#include <string>

namespace Snake::Data {
// #region Base
Sprite Sprites::head_right = Sprite(std::vector<std::u32string>{
    U"(.)\\- ",
    U"---bb>",
    U"(.)/- ",
});
Sprite Sprites::head_left = Sprite(std::vector<std::u32string>{
    U" -/(.)",
    U"<bb---",
    U" -\\(.)",
});
Sprite Sprites::head_up = Sprite(std::vector<std::u32string>{
    U" -^^- ",
    U"/ || \\",
    U"(.)(.)",
});
Sprite Sprites::head_down = Sprite(std::vector<std::u32string>{
    U"(.)(.)",
    U"\\ || /",
    U" -vv- ",
});
// #endregion
} // namespace Snake::Data
