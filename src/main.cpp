#include "GameManager/GameManager.h"
#include "iostream"
#include "objects/SpriteRenderer/SpriteRenderer.h"
#include "rendering/Config/Config.h"


using namespace Snake;
using namespace Rendering;

int main() {
  Config::ConfigureConsole();
  GameManager::Initialize();

  return 0;
}
