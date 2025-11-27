#include "Display.h"
#include "../../data/Renderables/Renderables.h"
#include "iostream"
#include <codecvt>
#include <queue>
#include <windows.h>

using namespace std;
using namespace Snake::Data;

namespace Snake {
namespace Rendering {


wchar_t Display::screenBuffer[RESOLUTION_X][RESOLUTION_Y];
wchar_t Display::frameBuffer[RESOLUTION_X][RESOLUTION_Y];
wchar_t Display::background[RESOLUTION_X][RESOLUTION_Y];

// u32string Display::ToU32String(string value) {
//   wstring_convert<codecvt_utf8<char32_t>, char32_t> conv;
//   return conv.from_bytes(value);
// }

// string Display::ToString(u32string value) {
//   wstring_convert<codecvt_utf8<char32_t>, char32_t> conv;
//   return conv.to_bytes(value);
// }

void Display::Init() {
  for (size_t y = 0; y < RESOLUTION_Y; y++) {
    for (size_t x = 0; x < RESOLUTION_X; x++) {
      screenBuffer[x][y] = ' ';
    }
  }

  for (int y = 0; y < RESOLUTION_Y; ++y) {
    for (int x = 0; x < RESOLUTION_X; ++x) {
      wchar_t ch;

      bool top = (y == 0);
      bool bottom = (y == RESOLUTION_Y - 1);
      bool left = (x == 0);
      bool right = (x == RESOLUTION_X - 1);

      bool gridRow = (y % 2 == 0) || y == RESOLUTION_Y - 1;
      bool gridCol = (x % 4 == 0) || x == RESOLUTION_X - 1;

      if (top && left) {
        ch = U'\u250C'; // ┌
      } else if (top && right) {
        ch = U'\u2510'; // ┐
      } else if (bottom && left) {
        ch = U'\u2514'; // └
      } else if (bottom && right) {
        ch = U'\u2518'; // ┘
      } else if (top && gridCol) {
        ch = U'\u252C'; // ┬ (top T)
      } else if (bottom && gridCol) {
        ch = U'\u2534'; // ┴ (bottom T)
      } else if (left && gridRow) {
        ch = U'\u251C'; // ├ (left T)
      } else if (right && gridRow) {
        ch = U'\u2524'; // ┤ (right T)
      } else if (gridRow && gridCol) {
        ch = U'\u253C'; // ┼ (cross)
      } else if (gridRow) {
        ch = U'\u2500'; // ─ (horizontal)
      } else if (gridCol) {
        ch = U'\u2502'; // │ (vertical)
      } else {
        ch = U'#'; // inside cell
      }
      background[x][y] = ch;
      frameBuffer[x][y] = ch;
    }
  }

  HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
  for (size_t y = 0; y < RESOLUTION_Y; y++) {
    for (size_t x = 0; x < RESOLUTION_X; x++) {
      COORD consolePos = {static_cast<SHORT>(x), static_cast<SHORT>(y)};
      SetConsoleCursorPosition(h, consolePos);

      wchar_t ch = static_cast<wchar_t>(background[x][y]);
      DWORD written;
      WriteConsoleW(h, &ch, 1, &written, nullptr);
    }
  }
}

void Display::Render() {

  Renderable &rend = Renderables::testRenderable();
  HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

  for (size_t y = 0; y < RESOLUTION_Y; y++) {
    for (size_t x = 0; x < RESOLUTION_X; x++) {
      frameBuffer[x][y] = background[x][y];
    }
  }

  int updates = 0;
  for (size_t y = 0; y < RESOLUTION_Y; y++) {
    for (size_t x = 0; x < RESOLUTION_X; x++) {
      COORD consolePos = {static_cast<SHORT>(x), static_cast<SHORT>(y)};
      SetConsoleCursorPosition(h, consolePos);

      wchar_t ch = background[x][y];
      DWORD written;
      WriteConsoleW(h, &ch, 1, &written, nullptr);
    }
  }
}
} // namespace Rendering
} // namespace Snake

