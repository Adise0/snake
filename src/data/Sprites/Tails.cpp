
#include "Sprites.h"
#include <string>

namespace Snake::Data {
// #region Base
Sprite Sprites::tail_right = Sprite(std::vector<std::u32string>{
    U"-/^---",
    U"<b--##",
    U"-\\v---",
});
Sprite Sprites::tail_left = Sprite(std::vector<std::u32string>{
    U"---^\\-",
    U"##--b>",
    U"---v/-",
});

Sprite Sprites::tail_up = Sprite(std::vector<std::u32string>{
    U"|b##b|",
    U"|b||b|",
    U"< ^^ >",
});
Sprite Sprites::tail_down = Sprite(std::vector<std::u32string>{
    U"< ^^ >",
    U"|b||b|",
    U"|b##b|",
});
// #endregion

// #region Corners
Sprite Sprites::tail_V_UR = Sprite(std::vector<std::u32string>{
    U"-/^---",
    U"/b//b/",
    U"< ^^ >",
});
Sprite Sprites::tail_V_UL = Sprite(std::vector<std::u32string>{
    U"---^\\-",
    U"\\b\\\\b\\",
    U"< ^^ >",
});

Sprite Sprites::tail_V_DL = Sprite(std::vector<std::u32string>{
    U"< ^^ >",
    U"/b//b/",
    U"---v/-",
});
Sprite Sprites::tail_V_DR = Sprite(std::vector<std::u32string>{
    U"< ^^ >",
    U"\\b\\\\b\\",
    U"-\\v---",
});

Sprite Sprites::tail_H_RD = Sprites::tail_V_UR;
Sprite Sprites::tail_H_LD = Sprites::tail_V_UL;
Sprite Sprites::tail_H_LU = Sprites::tail_V_DL;
Sprite Sprites::tail_H_RU = Sprites::tail_V_DR;
// #endregion

// #region Aliasess

// #endregion
} // namespace Snake::Data


