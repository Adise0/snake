#include "GameManager.h"
#include "../rendering/Display/Display.h"
#include <chrono>

using namespace Snake;
using namespace Rendering;

CellType GameManager::cells[Consts::MAP_X][Consts::MAP_Y];
std::queue<Vector2> GameManager::snake;

void GameManager::Initialize() {
  // #region Initialize
  Display::Initialize();
  InitializeGrid();


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

void GameManager::Tick(float deltaTime) { Display::Tick(); }

