#pragma once
namespace Snake::Data {
class Consts {
public:
  /// @brief The map horizontal size (in cells)
  static const int MAP_X;
  /// @brief The map vertical size (in cells)
  static const int MAP_Y;

  /// @brief The horizontal size of each cell (in characters)
  static const int CELL_RESOLUTION_X;

  /// @brief The vertical size of each cell (in characters)
  static const int CELL_RESOLUTION_Y;

  /// @brief The horizontal size of a Conssolas character (in pixels)
  static const int CHAR_RESOLUTION_X;
  /// @brief The vertical size of a Conssolas character (in pixels)
  static const int CHAR_RESOLUTION_Y;

  /// @brief The horizontal size of the whole map (in characters)
  static const int RESOLUTION_X;
  /// @brief The verrtical size of the whole map (in characters)
  static const int RESOLUTION_Y;
};
} // namespace Snake::Data
