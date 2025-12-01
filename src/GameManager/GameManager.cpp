#include "GameManager.h"
#include "../rendering/Display/Display.h"
#include <chrono>

using namespace Snake;
using namespace Rendering;

CellType GameManager::cells[Consts::MAP_X][Consts::MAP_Y];
std::queue<Vector2> GameManager::snake;

void GameManager::Initialize() {
  Display::Initialize();

  auto lastFrame = std::chrono::high_resolution_clock::now();

  while (true) {

    auto thisFrame = std::chrono::high_resolution_clock::now();
    float deltaTime = std::chrono::duration<float>(thisFrame - lastFrame).count();
    lastFrame = thisFrame;

    Tick(deltaTime);
  }
}

void GameManager::Tick(float deltaTime) { Display::Tick(); }

