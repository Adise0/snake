#include "iostream"
#include "rendering/Display/Display.h"
#include <windows.h>

int main() {

  SetConsoleOutputCP(CP_UTF8);

  Snake::Rendering::Display::Render();

  return 0;
}
