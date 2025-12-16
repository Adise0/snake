#include "../data/Consts/Consts.h"
#include "../objects/SpriteRenderer/SpriteRenderer.h"
#include "../objects/Vector2/Vector2.h"
#include <deque>
#include <optional>
#include <queue>
#include <vector>

using namespace Snake::Data;
using namespace Snake::Objects;

namespace Snake {
class GameManager {
private:
  /// @brief The current apple position
  static Vector2 applePosition;
  /// @brief The snake dequeue
  static std::deque<Vector2> snake;

  /// @brief The offset vector for screen positioning
  static Vector2 offset;

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

  /// @brief The stored snake body renderers
  static std::queue<SpriteRenderer> snakeRenderers;

  /// @brief The current frame counter
  static int currentFrame;
  /// @brief The current tick counter
  static int currentTick;

  /// @brief Whether the game is being played
  static bool isPlaying;
  /// @brief Whether the game is over
  static bool isGameOver;

  /// @brief The current ticks per second
  static float ticksPerSecond;
  /// @brief The fixed delta time between ticks
  static float fixedDeltaTime;
  /// @brief The time since the start of this fixed tick
  static float currentTickTimer;


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

  /// @brief Gets the fixed delta time between ticks
  /// @return The computed fixed delta time
  static float GetFixedDeltaTime();

  /// @brief Gets a new safe apple position
  /// @return The new apple position
  static Vector2 GetNewApplePossition();

  /// @brief Checks if the given cell is safe. (Not a wall or snake body)
  /// @param cell The cell to check
  /// @return Whether it's safe
  static bool IsCellSafe(Vector2 cell);

  /// @brief Spawns the snake in the center of the grid
  static void SpawnSnake();

  /// @brief Spawns the head renderer
  /// @param position The position to spawn the renderer at
  static void SpawnHeadRenderer(Vector2 position);
  /// @brief Spawns the tail renderer
  /// @param position The position to spawn the renderer at
  static void SpawnTailRenderer(Vector2 position);

  /// @brief Checks whether the given key is pressed
  /// @param key The key to check
  /// @return Whether it is pressed
  static bool IsKeyPressed(int key);

  /// @brief Gets the current input direction
  /// @return The new direction vector
  static Vector2 GetInputDirection();

  /// @brief Moves the snake to the next cell
  /// @param nextCell The next cell to move to
  /// @param didConsumeApple Whether the snake consumed an apple
  static void MoveSnake(Vector2 nextCell, bool didConsumeApple);

  /// @brief Ends the game
  static void EndGame();

  /// @brief Creates the body segment renderer
  static void CreateBodyRenderer();

  /// @brief Updates the head and tail renderers
  /// @param tickProgression The current tick fixxed progression (0-1)
  static void UpdateRenderers(float tickProgression);

  /// @brief Updates the passed renderer
  /// @param renderer The renderer to update
  /// @param prevPosition The initial fixedTickPosition of the renderer
  /// @param nextPosition The target position for the end of the tick
  /// @param tickProgression The current tick fixxed progression (0-1)
  static void UpdateRenderer(SpriteRenderer *renderer, Vector2 prevPosition, Vector2 nextPosition,
                             float tickProgression);

  /// @brief Updates the head and tail sprite renderers
  static void UpdateSprites();



  /// @brief Gets the correct body sprite based on the previous and next direction
  /// @param prevDir The previous direction
  /// @param nextDir The next direction
  /// @return The correct body sprite
  static Sprite *GetBodySprite(Vector2 prevDir, Vector2 nextDir);


  /// @brief Gets the correct head sprite based on the current direction
  /// @return The correct head sprite
  static Sprite *GetHeadSprite();


  /// @brief Gets the correct tail sprite based on the previous and next direction
  /// @param prevDir The previous direction
  /// @param nextDir The next direction
  /// @return The correct tail sprite
  static Sprite *GetTailSprite(Vector2 prevDir, Vector2 nextDir);
};
} // namespace Snake
