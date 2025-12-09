#include "GameManager.h"
#include "../data/Sprites/Sprites.h"
#include "../rendering/Display/Display.h"
#include <algorithm>
#include <chrono>
#include <iostream>

using namespace Snake;
using namespace Rendering;
using namespace Data;

std::optional<Vector2> GameManager::applePosition = std::nullopt;
std::deque<Vector2> GameManager::snake;
std::deque<SpriteRenderer> GameManager::snakeRenderers;
int GameManager::tick = 0;
int GameManager::frame = 0;
bool GameManager::isPlaying = false;
bool GameManager::isGameOver = false;

float GameManager::tickTimer = 0.0f;
const float GameManager::fixedDelta = std::pow(Consts::TICKS_PER_SECOND, -1);

Vector2 GameManager::currentDirection = Vector2::Zero;
Vector2 GameManager::prevDirection = Vector2::Zero;
Vector2 GameManager::bufferedDirection = Vector2::Zero;

SpriteRenderer *GameManager::headRenderer = nullptr;
// SpriteRenderer *GameManager::neckRenderer = nullptr;
SpriteRenderer *GameManager::tailRenderer = nullptr;
SpriteRenderer *GameManager::appleRenderer = nullptr;

Sprite *GameManager::tailSprite = nullptr;


void GameManager::Initialize() {
  // #region Initialize
  Display::Initialize();

  SpawnSnake();

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

  if (headRenderer == nullptr) {
    headRenderer = new SpriteRenderer(screenPosition, &Sprites::head_right);
    headRenderer->sortingLayer = 1;
  } else headRenderer->position = screenPosition;


  // if (neckRenderer == nullptr) {
  //   neckRenderer = new SpriteRenderer(screenPosition, &Sprites::neck_right);
  // } else neckRenderer->position = screenPosition;

  if (tailRenderer == nullptr) {
    tailRenderer = new SpriteRenderer(screenPosition, &Sprites::tail_right);
    tailRenderer->render = false;
    tailRenderer->sortingLayer = 1;
  } else {
    tailRenderer->position = screenPosition;
    tailRenderer->render = false;
  }



  std::cout << "Snake init!";
  // #endregion
}

bool GameManager::IsCellSafe(Vector2 cell) {
  if (cell.x < 0 || cell.x > Consts::MAP_X - 1 || cell.y < 0 || cell.y > Consts::MAP_Y - 1)
    return false;

  for (Vector2 snakCell : snake) {
    if (snakCell == cell) return false;
  }
  return true;
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

  Vector2 offset = Vector2(Consts::CELL_RESOLUTION_X, Consts::CELL_RESOLUTION_Y);
  Vector2 screenPos = pos * offset;
  if (appleRenderer == nullptr) {
    appleRenderer = new SpriteRenderer(screenPos, &Sprites::apple);
  } else appleRenderer->position = screenPos;

  return pos;
  // #endregion
}

void GameManager::Tick(float deltaTime) {
  // #region Tick
  Vector2 direction = GetNewDirection();

  if (direction == Vector2::Zero && !isPlaying) return;
  else if (!isGameOver) {
    isPlaying = true;
  }

  if (!isPlaying) return;
  if (applePosition == std::nullopt) applePosition = GetNewApplePossition();


  if (direction != Vector2::Zero && direction != currentDirection.Inverse())
    bufferedDirection = direction;

  Vector2 offset = Vector2(Consts::CELL_RESOLUTION_X, Consts::CELL_RESOLUTION_Y);
  tickTimer += deltaTime;

  float tickProgression = tickTimer / fixedDelta;
  tickProgression = std::clamp(tickProgression, 0.0f, 1.0f);


  Vector2 prevHeadPos = snake.front() - currentDirection;
  Vector2 targetHeadPos = snake.front();

  headRenderer->position =
      (prevHeadPos * offset) + ((targetHeadPos - prevHeadPos) * offset * tickProgression);

  // neckRenderer->position = headRenderer->position;

  if (snake.size() > 1) {
    Vector2 tailDirection =
        snake.size() <= 2 ? prevDirection : snake[snake.size() - 2] - snake.back();

    Vector2 prevTailPos = snake.back();
    Vector2 targetTailPos = snake.back() + tailDirection;

    if (snake.size() <= 2) {
      prevTailPos = snake.back() - tailDirection;
      targetTailPos = snake.back();
    } else {
      prevTailPos = snake.back();
      targetTailPos = snake.back() + tailDirection;
    }

    tailRenderer->position =
        (prevTailPos * offset) + ((targetTailPos - prevTailPos) * offset * tickProgression);
  }


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



void GameManager::FixedTick() {
  // #region FixedTick

  if (!isPlaying || bufferedDirection == Vector2::Zero || isGameOver) return;


  if (prevDirection != currentDirection) prevDirection = currentDirection;
  if (currentDirection != bufferedDirection) currentDirection = bufferedDirection;


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

  Vector2 offset = Vector2(Consts::CELL_RESOLUTION_X, Consts::CELL_RESOLUTION_Y);
  bool didConsumeApple = applePosition == nextCell;



  COORD coord = {0, 1};
  SetConsoleCursorPosition(Display::consoleHandle, coord);
  // std::cout << "\33[2K\r";
  // std::cout << "Snake size: " << snake.size() << " Renderer size: " << snakeRenderers.size();

  snake.push_front(nextCell);

  Sprite *sprite = &Sprites::body_V;
  if (snake.size() >= 3) {
    Vector2 nextHeadDirection = snake[0] - snake[1];
    Vector2 prevHeadDirection = snake[1] - snake[2];

    std::cout << "\33[2K\r";

    if (prevHeadDirection == Vector2::Up) {
      if (nextHeadDirection == Vector2::Up) {
        sprite = &Sprites::body_V;
      }
      if (nextHeadDirection == Vector2::Right) {
        sprite = &Sprites::body_V_UR;
      }
      if (nextHeadDirection == Vector2::Left) {
        sprite = &Sprites::body_V_UL;
      }
    }
    if (prevHeadDirection == Vector2::Down) {
      if (nextHeadDirection == Vector2::Down) {
        sprite = &Sprites::body_V;
      }
      if (nextHeadDirection == Vector2::Right) {
        sprite = &Sprites::body_V_DR;
      }
      if (nextHeadDirection == Vector2::Left) {
        sprite = &Sprites::body_V_DL;
      }
    }
    if (prevHeadDirection == Vector2::Right) {
      if (nextHeadDirection == Vector2::Right) {
        sprite = &Sprites::body_H;
      }
      if (nextHeadDirection == Vector2::Up) {
        sprite = &Sprites::body_H_LU;
      }
      if (nextHeadDirection == Vector2::Down) {
        sprite = &Sprites::body_H_LD;
      }
    }
    if (prevHeadDirection == Vector2::Left) {
      if (nextHeadDirection == Vector2::Left) {
        sprite = &Sprites::body_H;
      }
      if (nextHeadDirection == Vector2::Up) {
        sprite = &Sprites::body_H_RU;
      }
      if (nextHeadDirection == Vector2::Down) {
        sprite = &Sprites::body_H_RD;
      }
    }

  } else {
    Vector2 singleDir = snake[0] - snake[1];
    if (singleDir == Vector2::Left || singleDir == Vector2::Right) sprite = &Sprites::body_H;
    else sprite = &Sprites::body_V;
  }


  snakeRenderers.emplace_front(currentCell * offset, sprite);
  if (snake.size() == 3 && !tailRenderer->render) {
    tailRenderer->render = true;
  }

  if (didConsumeApple) {
    applePosition = std::nullopt;
  } else {
    snake.back();
    snake.pop_back();
    if (snakeRenderers.size() != 0) {
      snakeRenderers.pop_back();
    }
  }

  if (currentDirection == Vector2::Right && headRenderer->sprite != &Sprites::head_right) {
    headRenderer->sprite = &Sprites::head_right;
  }
  if (currentDirection == Vector2::Left && headRenderer->sprite != &Sprites::head_left) {
    headRenderer->sprite = &Sprites::head_left;
  }
  if (currentDirection == Vector2::Up && headRenderer->sprite != &Sprites::head_up) {
    headRenderer->sprite = &Sprites::head_up;
  }
  if (currentDirection == Vector2::Down && headRenderer->sprite != &Sprites::head_down) {
    headRenderer->sprite = &Sprites::head_down;
  }

  Sprite *nextTailSprite = &Sprites::tail_down;
  if (snake.size() >= 2) {
    Vector2 prevTailDirection;
    Vector2 tailDirection;

    if (snake.size() == 2) {
      prevTailDirection = prevDirection;
      tailDirection = currentDirection;
    } else {
      prevTailDirection = snake[snake.size() - 2] - snake.back();
      tailDirection = snake[snake.size() - 3] - snake[snake.size() - 2];
    }
    std::cout << "\33[2K\r";
    std::cout << "PrevTailDir: (" << prevTailDirection.x << ", " << prevTailDirection.y
              << ") TailDir: (" << tailDirection.x << ", " << tailDirection.y << ")";

    if (prevTailDirection == Vector2::Up) {
      if (tailDirection == Vector2::Up) nextTailSprite = &Sprites::tail_up;
      if (tailDirection == Vector2::Right) nextTailSprite = &Sprites::tail_V_UR;
      if (tailDirection == Vector2::Left) nextTailSprite = &Sprites::tail_V_UL;
    }
    if (prevTailDirection == Vector2::Down) {
      if (tailDirection == Vector2::Down) nextTailSprite = &Sprites::tail_down;
      if (tailDirection == Vector2::Right) nextTailSprite = &Sprites::tail_V_DR;
      if (tailDirection == Vector2::Left) nextTailSprite = &Sprites::tail_V_DL;
    }
    if (prevTailDirection == Vector2::Right) {
      if (tailDirection == Vector2::Right) nextTailSprite = &Sprites::tail_right;
      if (tailDirection == Vector2::Up) nextTailSprite = &Sprites::tail_H_LU;
      if (tailDirection == Vector2::Down) nextTailSprite = &Sprites::tail_H_LD;
    }
    if (prevTailDirection == Vector2::Left) {
      if (tailDirection == Vector2::Left) nextTailSprite = &Sprites::tail_left;
      if (tailDirection == Vector2::Up) nextTailSprite = &Sprites::tail_H_RU;
      if (tailDirection == Vector2::Down) nextTailSprite = &Sprites::tail_H_RD;
    }
  }

  if (snake.size() == 2) {
    tailRenderer->sprite = nextTailSprite;
    tailSprite = nextTailSprite;
  } else {
    if (tailSprite != nullptr) tailRenderer->sprite = tailSprite;
    tailSprite = nextTailSprite;
  }



  if (snake.size() > 2) {
    for (size_t i = 1; i < snake.size(); i++) {
      snakeRenderers[i - 1].position = snake[i] * offset;
    }
  }

  tick++;
  tickTimer = 0.0f;
  // #endregion
}

