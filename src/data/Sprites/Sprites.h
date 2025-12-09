#include "../../objects/Sprite/Sprite.h"

using namespace Snake::Objects;

namespace Snake::Data {
class Sprites {
public:
  static Sprite head_right;
  static Sprite head_left;
  static Sprite head_up;
  static Sprite head_down;

  static Sprite tail_right;
  static Sprite tail_left;
  static Sprite tail_up;
  static Sprite tail_down;

  static Sprite body_vert;
  static Sprite body_horiz;

  static Sprite body_VDR;
  static Sprite body_VDL;
  static Sprite body_VUR;
  static Sprite body_VUL;

  static Sprite body_HRU;
  static Sprite body_HLU;
  static Sprite body_HRD;
  static Sprite body_HLD;

  static Sprite apple;
};
} // namespace Snake::Data
