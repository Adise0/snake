#include "Config.h"
#include "../../data/Consts/Consts.h"
#include <iostream>
#include <windows.h>

using namespace Snake::Data;

namespace Snake::Rendering {

void Config::ConfigureConsole() {
  std::srand(time(0));

  SetConsoleEncoding();
  SetConsoleSize();
}

void Config::SetConsoleEncoding() {
  SetConsoleCP(CP_UTF8);
  SetConsoleOutputCP(CP_UTF8);
}

void Config::SetConsoleSize() {

  HWND hwnd = GetConsoleWindow();
  Sleep(20);
  HWND owner = GetWindow(hwnd, GW_OWNER);

  //TOODO: Grab actual font values!

  int width = Consts::RESOLUTION_X * Consts::CHAR_RESOLUTION_X;
  int height = Consts::RESOLUTION_Y * Consts::CHAR_RESOLUTION_Y;


  if (owner == NULL) {
    SetWindowPos(hwnd, nullptr, 0, 0, 100, height, SWP_NOZORDER | SWP_NOMOVE);

    DWORD mode;
    GetConsoleMode(hwnd, &mode);

    // Turn off echo and line buffering
    mode &= ~(ENABLE_ECHO_INPUT | ENABLE_LINE_INPUT);
    SetConsoleMode(hwnd, mode);

  } else {
    SetWindowPos(owner, nullptr, 0, 0, width, height, SWP_NOZORDER | SWP_NOMOVE);

    DWORD mode;
    GetConsoleMode(owner, &mode);

    // Turn off echo and line buffering
    mode &= ~(ENABLE_ECHO_INPUT | ENABLE_LINE_INPUT);
    SetConsoleMode(owner, mode);
  }
}
} // namespace Snake::Rendering
