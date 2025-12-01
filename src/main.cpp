#include "iostream"
#include "rendering/Config/Config.h"
#include "rendering/Display/Display.h"

using namespace Snake::Rendering;

int main() {
  Config::ConfigureConsole();
  Display::Initialize();
  Display::Tick();


  system("pause");
  return 0;
}
