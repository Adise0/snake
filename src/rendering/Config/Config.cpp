#include "Config.h"
#include "../../data/Consts/Consts.h"
#include <iostream>
#include <windows.h>

using namespace Snake::Data;

namespace Snake::Rendering {

void Config::ConfigureConsole() {
  // #region ConfigureConsole
  std::srand(time(0));

  SetConsoleEncoding();
  SetConsoleSize();
  // #endregion
}

void Config::SetConsoleEncoding() {
  // #region SetConsoleEncoding
  SetConsoleCP(CP_UTF8);
  SetConsoleOutputCP(CP_UTF8);
  // #endregion
}

void Config::SetConsoleSize() {
  // #region SetConsoleSize
  HWND hwnd = GetConsoleWindow();
  Sleep(20);
  HWND owner = GetWindow(hwnd, GW_OWNER);

  //TOODO: Grab actual font values!
  // I have not found a reliable way to do this so I hardcoded char resolutions

  int width = Consts::RESOLUTION_X * Consts::CHAR_RESOLUTION_X;
  int height = (Consts::RESOLUTION_Y + (Consts::TOP_OFFSET * Consts::CELL_RESOLUTION_Y)) *
               Consts::CHAR_RESOLUTION_Y;


  if (owner == NULL) {
    SetWindowPos(hwnd, nullptr, 0, 0, width, height, SWP_NOZORDER | SWP_NOMOVE);

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
  // #endregion
}
} // namespace Snake::Rendering
