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
  /// @brief The snake dequeue
  static std::deque<Vector2> snake;


  /// @brief The previous tail direction
  static Vector2 prevTailDirection;
  /// @brief The current head direction
  static Vector2 currentDirection;
  /// @brief The buffered input direction
  static Vector2 bufferedDirection;

  /// @brief The head renderer
  static SpriteRenderer *headRenderer;
  /// @brief The tail renderer
  static SpriteRenderer *tailRenderer;
  /// @brief The apple renderer
  static SpriteRenderer *appleRenderer;

  /// @brief The current frame counter
  static int currentFrame;
  /// @brief The current tick counter
  static int currentTick;

  /// @brief Whether the game is being played
  static bool isPlaying;
  /// @brief Whether the game is over
  static bool isGameOver;

  static const float deltaTimeAccumulator;
  static const float fixedDeltaTime;


public:
  /// @brief Initializes the GameManager
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
  static Vector2 GetInputDirection();
};
} // namespace Snake
