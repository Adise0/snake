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

SpriteRenderer *GameManager::headRenderer = nullptr;
SpriteRenderer *GameManager::tailRenderer = nullptr;
SpriteRenderer *GameManager::appleRenderer = nullptr;

int GameManager::currentFrame = 0;
int GameManager::currentTick = 0;

bool GameManager::isPlaying = false;
bool GameManager::isGameOver = false;

float GameManager::ticksPerSecond = 6.0f;
float GameManager::fixedDeltaTime = 0.0f;


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

  float accumulator = 0.0f;

  while (!isGameOver) {

    auto thisFrame = std::chrono::high_resolution_clock::now();
    float deltaTime = std::chrono::duration<float>(thisFrame - lastFrame).count();
    lastFrame = thisFrame;

    accumulator += deltaTime;
    if (accumulator >= fixedDeltaTime) {
      accumulator = 0;
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

  if (inputedDirection != Vector2::Zero && inputedDirection != currentDirection.Inverse())
    bufferedDirection = inputedDirection;
  // #endregion
}

void GameManager::FixedTick() {
  // #region FixedTick

  // #endregion
}


// #region Utils
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
    tailRenderer->render = false;
    return;
  }

  tailRenderer = new SpriteRenderer(position, &Sprites::tail_right);
  tailRenderer->render = false;
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



void GameManager::SpawnSnake() {
  // #region SpawnSnake
  snake.clear();
  Vector2 centerCell = Vector2(Consts::MAP_X / 2, Consts::MAP_Y / 2);
  snake.push_front(centerCell);


  Vector2 screenPosition =
      Vector2(centerCell.x * Consts::CELL_RESOLUTION_X, centerCell.y * Consts::CELL_RESOLUTION_Y);

  SpawnHeadRenderer(screenPosition);
  SpawnTailRenderer(screenPosition);
  // #endregion
}
// #endregion



