#include "Display.h"
#include "../../data/Renderables/Renderables.h"
#include "iostream"
#include <codecvt>
#include <queue>
#include <windows.h>

using namespace std;
using namespace Snake::Data;
using namespace Snake::Objects;

namespace Snake {
namespace Rendering {


wchar_t Display::screenBuffer[RESOLUTION_X][RESOLUTION_Y];
wchar_t Display::frameBuffer[RESOLUTION_X][RESOLUTION_Y];
wchar_t Display::background[RESOLUTION_X][RESOLUTION_Y];
queue<Vector2> Display::dirtyChars = queue<Vector2>();

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
      bool gridCol = (x % 5 == 0) || x == RESOLUTION_X - 1;

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
        ch = U' '; // inside cell
      }
      background[x][y] = ch;
      frameBuffer[x][y] = ch;
    }
  }

  SetConsoleCP(CP_UTF8);
  HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

  CONSOLE_CURSOR_INFO cursorInfo;
  GetConsoleCursorInfo(h, &cursorInfo);

  cursorInfo.bVisible = FALSE;
  SetConsoleCursorInfo(h, &cursorInfo);

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
  HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

  for (size_t y = 0; y < RESOLUTION_Y; y++) {
    for (size_t x = 0; x < RESOLUTION_X; x++) {
      frameBuffer[x][y] = background[x][y];
    }
  }

  Renderable &rend = Renderables::snakeHead;
  for (size_t sy = 0; sy < rend.sprite->height; sy++) {
    for (size_t sx = 0; sx < rend.sprite->width; sx++) {
      int y = rend.position.y + sy;
      int x = rend.position.x + sx;

      if (rend.sprite->drawing[sy][sx] == ' ') continue;
      if (rend.sprite->drawing[sy][sx] == 'b') {
        frameBuffer[x][y] = ' ';
        continue;
      }

      frameBuffer[x][y] = rend.sprite->drawing[sy][sx];
    }
  }

  for (size_t y = 0; y < RESOLUTION_Y; y++) {
    for (size_t x = 0; x < RESOLUTION_X; x++) {
      if (screenBuffer[x][y] != frameBuffer[x][y]) {
        screenBuffer[x][y] = frameBuffer[x][y];
        dirtyChars.push(Vector2(x, y));
      }
    }
  }


  while (!dirtyChars.empty()) {
    Vector2 pos = dirtyChars.front();
    dirtyChars.pop();

    COORD consolePos = {static_cast<SHORT>(pos.x), static_cast<SHORT>(pos.y)};
    SetConsoleCursorPosition(h, consolePos);

    wchar_t ch = screenBuffer[(int)pos.x][(int)pos.y];
    DWORD written;
    WriteConsoleW(h, &ch, 1, &written, nullptr);
  }


  // for (size_t y = 0; y < RESOLUTION_Y; y++) {
  //   for (size_t x = 0; x < RESOLUTION_X; x++) {

  //   }
  // }

  // for (size_t y = 0; y < RESOLUTION_Y; y++) {
  //   for (size_t x = 0; x < RESOLUTION_X; x++) {
  //     screenBuffer[x][y] = frameBuffer[x][y];
  //   }
  // }
}
} // namespace Rendering
} // namespace Snake

