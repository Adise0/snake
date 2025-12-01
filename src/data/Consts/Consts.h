#pragma once
namespace Snake::Data {
class Consts {
public:
  /// @brief The map horizontal size (in cells)
  static constexpr int MAP_X = 17;
  /// @brief The map vertical size (in cells)
  static constexpr int MAP_Y = 15;

  /// @brief The horizontal size of each cell (in characters)
  static constexpr int CELL_RESOLUTION_X = 5;
  /// @brief The vertical size of each cell (in characters)
  static constexpr int CELL_RESOLUTION_Y = 2;

  /// @brief The horizontal size of a Conssolas character (in pixels)
  static constexpr int CHAR_RESOLUTION_X = 11;
  /// @brief The vertical size of a Conssolas character (in pixels)
  static constexpr int CHAR_RESOLUTION_Y = 22;

  /// @brief The horizontal size of the whole map (in characters)
  static constexpr int RESOLUTION_X = MAP_X * CELL_RESOLUTION_X + 1;
  /// @brief The verrtical size of the whole map (in characters)
  static constexpr int RESOLUTION_Y = MAP_Y * CELL_RESOLUTION_Y + 1;
};
} // namespace Snake::Data
