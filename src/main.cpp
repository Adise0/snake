#include "./rendering/Display/Display.h"
#include "GameManager/GameManager.h"
#include "iostream"
#include "rendering/Config/Config.h"
#include <iostream>
#include <windows.h>


using namespace Snake;
using namespace Rendering;

int main() {
  Config::ConfigureConsole();
  try {
    GameManager::Initialize();

  } catch (std::runtime_error error) {
    COORD coord = {0, 1};
    SetConsoleCursorPosition(Display::consoleHandle, coord);
    std::cout << "\33[2K\r";
    std::cout << "Runtime exception: " << error.what();
  } catch (...) {
    COORD coord = {0, 2};
    SetConsoleCursorPosition(Display::consoleHandle, coord);
    std::cout << "\33[2K\r";
    std::cout << "Unhandled runtime exception";
  }

  _sleep(1000);
  system("pause");
  return 0;
}
