#include "GameManager.h"
#include "../data/Sprites/Sprites.h"
#include "../rendering/Display/Display.h"
#include <algorithm>
#include <chrono>
#include <iostream>

using namespace Snake;
using namespace Rendering;
using namespace Data;


Vector2 GameManager::applePosition = Vector2(-1, -1);
std::deque<Vector2> GameManager::snake;

Vector2 GameManager::prevTailDirection = Vector2::Zero;
Vector2 GameManager::currentDirection = Vector2::Zero;
Vector2 GameManager::bufferedDirection = Vector2::Zero;
Vector2 GameManager::offset = Vector2(Consts::CELL_RESOLUTION_X, Consts::CELL_RESOLUTION_Y);

SpriteRenderer *GameManager::headRenderer = nullptr;
SpriteRenderer *GameManager::tailRenderer = nullptr;
SpriteRenderer *GameManager::appleRenderer = nullptr;
std::queue<SpriteRenderer> GameManager::snakeRenderers;


int GameManager::currentFrame = 0;
int GameManager::currentTick = 0;

bool GameManager::isPlaying = false;
bool GameManager::isGameOver = false;

float GameManager::ticksPerSecond = 6.0f;
float GameManager::fixedDeltaTime = 0.0f;
float GameManager::currentTickTimer = 0.0f;


void GameManager::Initialize() {
  // #region Initialize
  Display::Initialize();
  fixedDeltaTime = GetFixedDeltaTime();
  SpawnSnake();
  applePosition = GetNewApplePossition();

  Display::Tick();
  Run();
  // #endregion
}


void GameManager::Run() {
  // #region Run
  auto lastFrame = std::chrono::high_resolution_clock::now();

  while (!isGameOver) {

    auto thisFrame = std::chrono::high_resolution_clock::now();
    float deltaTime = std::chrono::duration<float>(thisFrame - lastFrame).count();
    lastFrame = thisFrame;

    currentTickTimer += deltaTime;
    if (currentTickTimer >= fixedDeltaTime) {
      currentTickTimer = 0;
      FixedTick();
    }

    Tick(deltaTime);
  }
  // #endregion
}


void GameManager::Tick(float deltaTime) {
  // #region Tick
  Vector2 inputedDirection = GetInputDirection();
  if (inputedDirection == Vector2::Zero && !isPlaying) return;
  else if (!isGameOver) isPlaying = true;

  if (!isPlaying) return;

  float tickProgression = currentTickTimer / fixedDeltaTime;
  tickProgression = std::clamp(tickProgression, 0.0f, 1.0f);


  if (inputedDirection != Vector2::Zero && inputedDirection != currentDirection.Inverse())
    bufferedDirection = inputedDirection;


  UpdateRenderers(tickProgression);

  currentFrame++;

  Display::Tick();
  // #endregion
}

void GameManager::FixedTick() {
  // #region FixedTick
  if (!isPlaying || bufferedDirection == Vector2::Zero || isGameOver) return;

  if (currentDirection != bufferedDirection) currentDirection = bufferedDirection;

  Vector2 currentCell = snake.front();
  Vector2 nextCell = currentCell + currentDirection;

  if (!IsCellSafe(nextCell)) {
    EndGame();
    return;
  }

  bool didConsumeApple = applePosition == nextCell;

  MoveSnake(nextCell, didConsumeApple);
  if (didConsumeApple) applePosition = GetNewApplePossition();

  currentTick++;
  // #endregion
}


// #region Utils
void GameManager::UpdateRenderers(float tickProgression) {
  // #region UpdateRenderers
  Vector2 prevHeadPos = snake.front() - currentDirection;
  Vector2 nextHeadPos = snake.front();
  UpdateRenderer(headRenderer, prevHeadPos, nextHeadPos, tickProgression);

  Vector2 prevTailPos = snake.back() - prevTailDirection;
  Vector2 nextTailPos = snake.back();
  UpdateRenderer(tailRenderer, prevTailPos, nextTailPos, tickProgression);
  // #endregion
}

void GameManager::UpdateRenderer(SpriteRenderer *renderer, Vector2 prevPosition,
                                 Vector2 nextPosition, float tickProgression) {
  // #regionUpdateRenderer
  Vector2 screenPosition =
      (prevPosition * offset) + ((nextPosition - prevPosition) * offset * tickProgression);

  renderer->position = screenPosition;
  // #endregion
}


float GameManager::GetFixedDeltaTime() {
  // #region GetFixedDeltaTime
  return 1.0f / ticksPerSecond;
  // #endregion
}

void GameManager::SpawnHeadRenderer(Vector2 position) {
  // #region SpawnHeadRenderer
  bool headRendererExists = headRenderer != nullptr;
  if (headRendererExists) {
    headRenderer->position = position;
    return;
  }

  headRenderer = new SpriteRenderer(position, &Sprites::head_right);
  headRenderer->sortingLayer = 1;
  // #endregion
}

void GameManager::SpawnTailRenderer(Vector2 position) {
  // #region SpawnHeadRenderer
  bool tailRendererExists = tailRenderer != nullptr;
  if (tailRendererExists) {
    tailRenderer->position = position;
    return;
  }

  tailRenderer = new SpriteRenderer(position, &Sprites::tail_right);
  tailRenderer->sortingLayer = 1;
  // #endregion
}

bool GameManager::IsKeyPressed(int key) {
  // #region IsKeyPressed
  return (GetAsyncKeyState(key) & 0x8000) != 0;
  // #endregion
}

Vector2 GameManager::GetInputDirection() {
  // #region GetInputDirection
  if (IsKeyPressed('W')) return Vector2::Up;
  if (IsKeyPressed('A')) return Vector2::Left;
  if (IsKeyPressed('S')) return Vector2::Down;
  if (IsKeyPressed('D')) return Vector2::Right;
  return Vector2::Zero;
  // #endregion
}

void GameManager::MoveSnake(Vector2 nextCell, bool didConsumeApple) {
  // #region MoveSnake
  snake.push_front(nextCell);
  prevTailDirection = snake[snake.size() - 2] - snake.back();
  if (!didConsumeApple) {
    snake.pop_back();
    if (snakeRenderers.size() != 0) snakeRenderers.pop();
  }

  UpdateSprites();
  // if (snake.size() < 2) return;
  CreateBodyRenderer();
  // #endregion
}

void GameManager::UpdateSprites() {
  // #region UpdateSprites
  Sprite *headSprite = GetHeadSprite();
  if (headRenderer->sprite != headSprite) headRenderer->sprite = headSprite;


  Vector2 nextTailDir = snake[snake.size() - 2] - snake.back();
  Sprite *tailSprite = GetTailSprite(prevTailDirection, nextTailDir);
  if (tailRenderer->sprite != tailSprite) tailRenderer->sprite = tailSprite;

  // #endregion
}

void GameManager::CreateBodyRenderer() {
  // #region CreateBodyRenderer
  Vector2 prevHeadDirection = snake[1] - snake[0];
  Vector2 nextHeadDirection = snake[2] - snake[1];

  Sprite *sprite = GetBodySprite(prevHeadDirection, nextHeadDirection);
  snakeRenderers.emplace(snake[1] * offset, sprite);
  // #endregion
}

Sprite *GameManager::GetBodySprite(Vector2 prevDir, Vector2 nextDir) {
  // #region GetBodySprite
  if (prevDir == Vector2::Up) {
    if (nextDir == Vector2::Up) return &Sprites::body_V;
    if (nextDir == Vector2::Right) return &Sprites::body_V_UR;
    if (nextDir == Vector2::Left) return &Sprites::body_V_UL;
  }

  if (prevDir == Vector2::Down) {
    if (nextDir == Vector2::Down) return &Sprites::body_V;
    if (nextDir == Vector2::Right) return &Sprites::body_V_DR;
    if (nextDir == Vector2::Left) return &Sprites::body_V_DL;
  }

  if (prevDir == Vector2::Right) {
    if (nextDir == Vector2::Right) return &Sprites::body_H;
    if (nextDir == Vector2::Up) return &Sprites::body_H_LU;
    if (nextDir == Vector2::Down) return &Sprites::body_H_LD;
  }

  if (prevDir == Vector2::Left) {
    if (nextDir == Vector2::Left) return &Sprites::body_H;
    if (nextDir == Vector2::Up) return &Sprites::body_H_RU;
    if (nextDir == Vector2::Down) return &Sprites::body_H_RD;
  }
  // Should never reach here
  throw std::runtime_error("Invalid body sprite directions " + std::to_string(prevDir.x) + "," +
                           std::to_string(prevDir.y) + " to " + std::to_string(nextDir.x) + "," +
                           std::to_string(nextDir.y));
  // #endregion
}

Sprite *GameManager::GetTailSprite(Vector2 prevDir, Vector2 nextDir) {
  // #region GetTailSprite
  if (prevDir == Vector2::Up) {
    if (nextDir == Vector2::Up) return &Sprites::tail_up;
    if (nextDir == Vector2::Right) return &Sprites::tail_V_UR;
    if (nextDir == Vector2::Left) return &Sprites::tail_V_UL;
  }
  if (prevDir == Vector2::Down) {
    if (nextDir == Vector2::Down) return &Sprites::tail_down;
    if (nextDir == Vector2::Right) return &Sprites::tail_V_DR;
    if (nextDir == Vector2::Left) return &Sprites::tail_V_DL;
  }
  if (prevDir == Vector2::Right) {
    if (nextDir == Vector2::Right) return &Sprites::tail_right;
    if (nextDir == Vector2::Up) return &Sprites::tail_H_LU;
    if (nextDir == Vector2::Down) return &Sprites::tail_H_LD;
  }
  if (prevDir == Vector2::Left) {
    if (nextDir == Vector2::Left) return &Sprites::tail_left;
    if (nextDir == Vector2::Up) return &Sprites::tail_H_RU;
    if (nextDir == Vector2::Down) return &Sprites::tail_H_RD;
  }
  // Should never reach here
  throw std::runtime_error("Invalid tail sprite directions " + std::to_string(prevDir.x) + "," +
                           std::to_string(prevDir.y) + " to " + std::to_string(nextDir.x) + "," +
                           std::to_string(nextDir.y));
  // #endregion
}


Sprite *GameManager::GetHeadSprite() {
  // #region GetHeadSprite
  if (currentDirection == Vector2::Right) {
    return &Sprites::head_right;
  }
  if (currentDirection == Vector2::Left) {
    return &Sprites::head_left;
  }
  if (currentDirection == Vector2::Up) {
    return &Sprites::head_up;
  }
  if (currentDirection == Vector2::Down) {
    return &Sprites::head_down;
  }
  // Should never reach here
  throw std::runtime_error("Invalid current direction");
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

    isPositionSafe = IsCellSafe(Vector2(x, y));
    if (isPositionSafe) pos = Vector2(x, y);
  }

  Vector2 screenPos = pos * offset;
  if (appleRenderer == nullptr) {
    appleRenderer = new SpriteRenderer(screenPos, &Sprites::apple);
  } else appleRenderer->position = screenPos;

  return pos;
  // #endregion
}

bool GameManager::IsCellSafe(Vector2 cell) {
  // #region IsCellSafe
  if (cell.x < 0 || cell.x > Consts::MAP_X - 1 || cell.y < 0 || cell.y > Consts::MAP_Y - 1)
    return false;

  for (Vector2 snakCell : snake) {
    if (snakCell == cell) return false;
  }
  return true;
  // #endregion
}

void GameManager::EndGame() {
  // #region EndGame
  COORD coord = {0, 1};
  SetConsoleCursorPosition(Display::consoleHandle, coord);
  std::cout << "Game over";
  isGameOver = true;
  isPlaying = false;
  // #endregion
}

void GameManager::SpawnSnake() {
  // #region SpawnSnake
  snake.clear();
  Vector2 centerCell = Vector2(Consts::MAP_X / 2, Consts::MAP_Y / 2);
  snake.push_front(centerCell);
  snake.push_back(centerCell + Vector2::Left);
  prevTailDirection = Vector2::Right;

  Vector2 headPosition = centerCell * offset;
  Vector2 tailPosition = (centerCell + Vector2::Left) * offset;

  SpawnHeadRenderer(headPosition);
  SpawnTailRenderer(tailPosition);
  // snakeRenderers.emplace(snake.back() * offset, &Sprites::body_H);
  // #endregion
}
// #endregion



