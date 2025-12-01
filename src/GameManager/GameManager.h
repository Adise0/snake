#include "../data/CellType/CellType.h"
#include "../data/Consts/Consts.h"
#include "../objects/Vector2/Vector2.h"
#include <queue>

using namespace Snake::Data;
using namespace Snake::Objects;

namespace Snake {
class GameManager {
private:
  /// @brief The cell grid
  static CellType cells[Consts::MAP_X][Consts::MAP_Y];
  /// @brief The snake queue
  static std::queue<Vector2> snake;


public:
  /// @brief Initializes the gameManager
  static void Initialize();

private:
  /// @brief The tick method. Ticks every frame
  /// @param deltaTime The delta time passed since last frame
  static void Tick(float deltaTime);

  /// @brief Initializes the grid
  static void InitializeGrid();

  /// @brief Runs the tick system
  static void Run();

  /// @brief Gets a new safe apple position
  /// @return The new apple position
  static Vector2 GetNewApplePossition();

  /// @brief Checks if the given cell is safe. (Not a wall or snake body)
  /// @param cell The cell to check
  /// @return Whether it's safe
  static bool IsCellSafe(Vector2 cell);
};
} // namespace Snake
