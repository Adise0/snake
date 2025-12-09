#include "Sprites.h"
#include <string>

namespace Snake::Data {

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


Sprite Sprites::tail_right = Sprite(std::vector<std::u32string>{
    U"-/^---",
    U"<b---b",
    U"-\\v---",
});
Sprite Sprites::tail_left = Sprite(std::vector<std::u32string>{
    U"---^\\-",
    U"b---b>",
    U"---v/-",
});
Sprite Sprites::tail_up = Sprite(std::vector<std::u32string>{
    U"|b||b|",
    U"|    |",
    U"< ^^ >",
});
Sprite Sprites::tail_down = Sprite(std::vector<std::u32string>{
    U"< ^^ >",
    U"|b||b|",
    U"|    |",
});

Sprite Sprites::body_horiz = Sprite(std::vector<std::u32string>{
    U"-----",
    U"#####",
    U"-----",
});
Sprite Sprites::body_vert = Sprite(std::vector<std::u32string>{
    U"|####|",
    U"|####|",
    U"|####|",
});

Sprite Sprites::body_VDL = Sprite(std::vector<std::u32string>{
    U"/bbbb|",
    U"bbbbb/",
    U"----bb",
});
Sprite Sprites::body_VDR = Sprite(std::vector<std::u32string>{
    U"|####L",
    U"\\#####",
    U"bb----",
});



Sprite Sprites::body_HLD = Sprite(std::vector<std::u32string>{
    U"----bb",
    U"bbbbb\\",
    U"\\bbbb|",
});
Sprite Sprites::body_HRD = Sprite(std::vector<std::u32string>{
    U"bb----",
    U"/bbbbb",
    U"|bbbbL",
});

Sprite Sprites::body_VUR = Sprites::body_HRD;
Sprite Sprites::body_VUL = Sprites::body_HLD;
Sprite Sprites::body_HLU = Sprites::body_VDL;
Sprite Sprites::body_HRU = Sprites::body_VDR;

Sprite Sprites::apple = Sprite(std::vector<std::u32string>{
    U"  ,  ",
    U" /-\\ ",
    U" \\_/ ",
});
} // namespace Snake::Data


