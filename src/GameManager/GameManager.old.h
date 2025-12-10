#include "../data/CellType/CellType.h"
#include "../data/Consts/Consts.h"
#include "../objects/SpriteRenderer/SpriteRenderer.h"
#include "../objects/Vector2/Vector2.h"
#include <deque>
#include <optional>
#include <vector>

using namespace Snake::Data;
using namespace Snake::Objects;

namespace Snake {
class GameManager {
private:
  /// @brief The current apple position
  static std::optional<Vector2> applePosition;
  /// @brief The snake queue
  static std::deque<Vector2> snake;
  static std::deque<SpriteRenderer> snakeRenderers;

  static SpriteRenderer *headRenderer;
  // static SpriteRenderer *neckRenderer;
  static SpriteRenderer *tailRenderer;
  // static SpriteRenderer *preTailRenderer;
  static SpriteRenderer *appleRenderer;


  static int frame;
  static int tick;
  static bool isPlaying;
  static bool isGameOver;
  static bool hasReachedTarget;

  static float tickTimer;
  static const float fixedDelta;

  static Vector2 currentDirection;
  static Vector2 bufferedDirection;
  static Vector2 prevDirection;

  static Sprite *tailSprite;

public:
  /// @brief Initializes the gameManager
  static void Initialize();

private:
  /// @brief The tick method. Ticks every frame
  /// @param deltaTime The delta time passed since last frame
  static void Tick(float deltaTime);

  /// @brief The fixed tick method. Ticks once a second
  static void FixedTick();

  /// @brief Runs the tick system
  static void Run();

  /// @brief Gets a new safe apple position
  /// @return The new apple position
  static Vector2 GetNewApplePossition();

  /// @brief Checks if the given cell is safe. (Not a wall or snake body)
  /// @param cell The cell to check
  /// @return Whether it's safe
  static bool IsCellSafe(Vector2 cell);

  /// @brief Spawns the snake in the center of the grid
  static void SpawnSnake();

  /// @brief Checks whether the given key is pressed
  /// @param key The key to check
  /// @return Whether it is pressed
  static bool IsKeyPressed(int key);

  /// @brief Gets the current input direction
  /// @return The new direction vector
  static Vector2 GetNewDirection();
};
} // namespace Snake
