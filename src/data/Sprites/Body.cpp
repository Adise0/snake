
#include "Sprites.h"
#include <string>

namespace Snake::Data {
// #region Base
Sprite Sprites::body_H = Sprite(std::vector<std::u32string>{
    U"-----",
    U"#####",
    U"-----",
});
Sprite Sprites::body_V = Sprite(std::vector<std::u32string>{
    U"|b##b|",
    U"|b##b|",
    U"|b##b|",
});
// #endregion

// #region Corners
Sprite Sprites::body_V_UR = Sprite(std::vector<std::u32string>{
    U"bb----",
    U"/#####",
    U"|b##bL",
});
Sprite Sprites::body_V_UL = Sprite(std::vector<std::u32string>{
    U"----bb",
    U"#####\\",
    U"\\b##b|",
});

Sprite Sprites::body_V_DL = Sprite(std::vector<std::u32string>{
    U"/b##b|",
    U"####b/",
    U"----bb",
});
Sprite Sprites::body_V_DR = Sprite(std::vector<std::u32string>{
    U"|b##bL",
    U"\\#####",
    U"bb----",
});



Sprite Sprites::body_H_RD = Sprites::body_V_UR;
Sprite Sprites::body_H_LD = Sprites::body_V_UL;
Sprite Sprites::body_H_LU = Sprites::body_V_DL;
Sprite Sprites::body_H_RU = Sprites::body_V_DR;
// #endregion

// #region Aliasess

// #endregion
} // namespace Snake::Data


