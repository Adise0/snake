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

  /// @brief The tick method. Ticks every frame
  /// @param deltaTime The delta time passed since last frame
  static void Tick(float deltaTime);

public:
  /// @brief Initializes the gameManager
  static void Initialize();
};
} // namespace Snake
