#include "GameManager/GameManager.h"
#include "iostream"
#include "rendering/Config/Config.h"


using namespace Snake;
using namespace Rendering;

int main() {
  Config::ConfigureConsole();
  GameManager::Initialize();

  _sleep(1000);
  system("pause");
  return 0;
}
