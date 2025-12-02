#include "GameManager.h"
#include "../data/Sprites/Sprites.h"
#include "../rendering/Display/Display.h"
#include <chrono>
#include <iostream>

using namespace Snake;
using namespace Rendering;
using namespace Data;

CellType GameManager::cells[Consts::MAP_X][Consts::MAP_Y];
std::optional<Vector2> GameManager::applePosition = std::nullopt;
std::deque<Vector2> GameManager::snake;
std::deque<SpriteRenderer> GameManager::snakeRenderers;
int GameManager::tick = 0;
int GameManager::frame = 0;
bool GameManager::isPlaying = false;
bool GameManager::isGameOver = false;

Vector2 GameManager::currentDirection = Vector2::Zero;
Vector2 GameManager::bufferedDirection = Vector2::Zero;

void GameManager::Initialize() {
  // #region Initialize
  Display::Initialize();

  InitializeGrid();
  SpawnSnake();

  Display::Tick();
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
  const float fixedDelta = std::pow(Consts::TICKS_PER_SECOND, -1); // Equivalent to 1/TicksPerSec
  float accumulator = 0.0f;

  while (!isGameOver) {

    auto thisFrame = std::chrono::high_resolution_clock::now();
    float deltaTime = std::chrono::duration<float>(thisFrame - lastFrame).count();
    lastFrame = thisFrame;

    accumulator += deltaTime;
    if (accumulator >= fixedDelta) {
      accumulator = 0;
      FixedTick();
    }

    Tick(deltaTime);
  }
  // #endregion
}


void GameManager::SpawnSnake() {
  // #region SpawnSnake

  int x = (Consts::MAP_X / 2);
  int y = (Consts::MAP_Y / 2);

  Vector2 spawnPos = Vector2(x, y);
  snake.push_front(spawnPos);

  Vector2 screenPosition = Vector2(x * Consts::CELL_RESOLUTION_X, y * Consts::CELL_RESOLUTION_Y);
  snakeRenderers.emplace_front(screenPosition, &Sprites::head_right);
  // #endregion
}

Vector2 GameManager::GetNewApplePossition() {
  // #region GetNewApplePossition
  bool isPositionSafe = false;
  short gridPositions = Consts::MAP_X * Consts::MAP_Y;

  Vector2 pos;

  while (!isPositionSafe) {
    int rnd = std::rand() % gridPositions;
    short x = rnd % Consts::MAP_X;
    short y = rnd / Consts::MAP_X;

    isPositionSafe = cells[x][y] != CellType::Snake;
    if (isPositionSafe) pos = Vector2(x, y);
  }
  return pos;
  // #endregion
}

void GameManager::Tick(float deltaTime) {
  // #region Tick
  Vector2 direction = GetNewDirection();

  if (direction == Vector2::Zero && !isPlaying) return;
  else if (!isGameOver) isPlaying = true;

  if (!isPlaying) return;


  if (applePosition == std::nullopt) applePosition = GetNewApplePossition();


  if (direction != Vector2::Zero && direction != currentDirection.Inverse())
    bufferedDirection = direction;

  Vector2 offset = Vector2(Consts::CELL_RESOLUTION_X, Consts::CELL_RESOLUTION_Y);

  // if (snakeRenderers.front().position / != snake.front()) {


  Vector2 newPos = snake.front() * offset;
  COORD coord = {0, 0};
  SetConsoleCursorPosition(Display::consoleHandle, coord);
  std::cout << "\33[2K\r" << "Dih: " << bufferedDirection.x << " - " << bufferedDirection.y;

  int step = currentDirection.x == 0 ? Consts::CELL_RESOLUTION_Y : Consts::CELL_RESOLUTION_X;

  Vector2 &headPosition = snakeRenderers.front().position;
  const float eps = 0.5f;
  bool alignedX = std::fabs(std::fmod(headPosition.x, (float)Consts::CELL_RESOLUTION_X)) < eps;
  bool alignedY = std::fabs(std::fmod(headPosition.y, (float)Consts::CELL_RESOLUTION_Y)) < eps;
  bool aligned = alignedX && alignedY;

  if (aligned && snakeDirection != currentDirection) snakeDirection = currentDirection;

  if (snakeRenderers.front().position != newPos) {
    snakeRenderers.front().position += snakeDirection * step * Consts::TICKS_PER_SECOND * deltaTime;
  }

  // }


  Display::Tick();
  // #endregion
}

bool GameManager::IsKeyPressed(int key) {
  // #region IsKeyPressed
  return (GetAsyncKeyState(key) & 0x8000) != 0;
  // #endregion
}

Vector2 GameManager::GetNewDirection() {
  // #region GetNewDirection
  if (IsKeyPressed('W')) return Vector2::Up;
  if (IsKeyPressed('A')) return Vector2::Left;
  if (IsKeyPressed('S')) return Vector2::Down;
  if (IsKeyPressed('D')) return Vector2::Right;
  return Vector2::Zero;
  // #endregion
}

bool GameManager::IsCellSafe(Vector2 cell) {
  if (cell.x < 0 || cell.x > Consts::MAP_X - 1 || cell.y < 0 || cell.y > Consts::MAP_Y - 1)
    return false;
  // TODO: Add snake collisioon
  return true;
}

void GameManager::FixedTick() {
  // #region FixedTick

  if (!isPlaying || bufferedDirection == Vector2::Zero || isGameOver) return;

  if (bufferedDirection != currentDirection) currentDirection = bufferedDirection;

  COORD coord = {0, 1};
  SetConsoleCursorPosition(Display::consoleHandle, coord);
  std::cout << "Next cell: " << currentDirection.x << " - " << currentDirection.y
            << " Tick: " << tick;
  tick++;

  Vector2 currentCell = snake.front();
  Vector2 nextCell = currentCell + currentDirection;



  if (!IsCellSafe(nextCell)) {
    COORD coord = {0, 1};
    SetConsoleCursorPosition(Display::consoleHandle, coord);
    std::cout << "Game over";
    isGameOver = true;
    isPlaying = false;
    return;
  }

  snake.push_front(nextCell);
  if (applePosition != nextCell) {
    snake.pop_back();
  }
  // #endregion
}

