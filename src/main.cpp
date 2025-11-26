#include "rendering/Display/Display.h"
#include <iostream>
#include <windows.h>

using namespace std;

int main() {

  SetConsoleOutputCP(CP_UTF8);
  SetConsoleCP(CP_UTF8);

  try {
    cout << "Starting application..." << endl;
    Snake::Rendering::Display::render();

  } catch (const std::exception &e) {
    std::cerr << e.what() << '\n';
    system("pause");
  }



  system("pause");
  return 0;
}
