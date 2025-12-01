#include "GameManager.h"
#include "../rendering/Display/Display.h"
#include <chrono>

using namespace Snake;
using namespace Rendering;

CellType GameManager::cells[Consts::MAP_X][Consts::MAP_Y];
std::optional<Vector2> GameManager::applePosition = std::nullopt;
std::deque<Vector2> GameManager::snake;
std::vector<SpriteRenderer *> GameManager::snakeRenderers;

void GameManager::Initialize() {
  // #region Initialize
  Display::Initialize();
  InitializeGrid();

  SpawnSnake();

  Run();
  // #endregion
}

void GameManager::InitializeGrid() {
  // #region InitializeGrid
  for (size_t y = 0; y < Consts::MAP_Y; y++) {
    for (size_t x = 0; x < Consts::MAP_X; x++) {
      cells[x][y] = CellType::Empty;
    }
  }
  // #endregion
}

void GameManager::Run() {
  // #region Run
  auto lastFrame = std::chrono::high_resolution_clock::now();

  while (true) {

    auto thisFrame = std::chrono::high_resolution_clock::now();
    float deltaTime = std::chrono::duration<float>(thisFrame - lastFrame).count();
    lastFrame = thisFrame;

    Tick(deltaTime);
  }
  // #endregion
}


void GameManager::SpawnSnake() {
  // #region SpawnSnake
  short x = Consts::MAP_X / 2;
  short y = Consts::MAP_Y / 2;

  snake.push_front(Vector2(x, y));
  // #endregion
}

Vector2 GameManager::GetNewApplePossition() {
  // #region GetNewApplePossition
  bool isPositionSafe = false;
  short gridPositions = Consts::MAP_X * Consts::MAP_Y;

  Vector2 pos;

  while (!isPositionSafe) {
    int rnd = std::rand() % gridPositions;
    short x = rnd % Consts::MAP_Y;
    short y = rnd / Consts::MAP_X;
    isPositionSafe = cells[x][y] != CellType::Snake;
    if (isPositionSafe) pos = Vector2(x, y);
  }
  return pos;
  // #endregion
}

void GameManager::Tick(float deltaTime) {
  // #region Tick
  if (applePosition == std::nullopt) applePosition = GetNewApplePossition();

  Display::Tick();
  // #endregion
}

