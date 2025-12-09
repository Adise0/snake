#include "../../objects/Sprite/Sprite.h"

using namespace Snake::Objects;

namespace Snake::Data {
class Sprites {
public:
  // #region Heads
  /// @brief The head sprite facing right
  static Sprite head_right;
  /// @brief The head sprite facing left
  static Sprite head_left;
  /// @brief The head sprite facing up
  static Sprite head_up;
  /// @brief The head sprite facing down
  static Sprite head_down;
  // #endregion

  // #region Tails
  static Sprite tail_right;
  static Sprite tail_left;
  static Sprite tail_up;
  static Sprite tail_down;

  // #region Corners
  /// @brief The tail corner sprite facing up-right ┌
  static Sprite tail_V_UR;
  /// @brief The tail corner sprite facing down-right ┐
  static Sprite tail_V_UL;
  /// @brief The tail corner sprite facing down-left ┘
  static Sprite tail_V_DL;
  /// @brief The tail corner sprite facing up-left └
  static Sprite tail_V_DR;

  /// @brief The tail corner sprite facing right-down┌ (Aliass for V_UR)
  static Sprite tail_H_RD;
  /// @brief The tail corner sprite facing left-down ┐ (Aliass for V_UL)
  static Sprite tail_H_LD;
  /// @brief The tail corner sprite facing left-up ┘ (Aliass for V_DL)
  static Sprite tail_H_LU;
  /// @brief The tail corner sprite facing right-up └ (Aliass for V_DR)
  static Sprite tail_H_RU;
  // #endregion
  // #endregion

  // #region Body
  static Sprite body_V;
  static Sprite body_H;

  // #region Corners
  /// @brief The body corner sprite facing up-right ┌
  static Sprite body_V_UR;
  /// @brief The body corner sprite facing down-right ┐
  static Sprite body_V_UL;
  /// @brief The body corner sprite facing down-left ┘
  static Sprite body_V_DL;
  /// @brief The body corner sprite facing up-left └
  static Sprite body_V_DR;

  /// @brief The body corner sprite facing right-down┌ (Aliass for V_UR)
  static Sprite body_H_RD;
  /// @brief The body corner sprite facing left-down ┐ (Aliass for V_UL)
  static Sprite body_H_LD;
  /// @brief The body corner sprite facing left-up ┘ (Aliass for V_DL)
  static Sprite body_H_LU;
  /// @brief The body corner sprite facing right-up └ (Aliass for V_DR)
  static Sprite body_H_RU;
  // #endregion
  // #endregion

  static Sprite apple;
};
} // namespace Snake::Data
