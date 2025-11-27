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


char32_t Display::screenBuffer[RESOLUTION_Y][RESOLUTION_X];
char32_t Display::frameBuffer[RESOLUTION_Y][RESOLUTION_X];
char32_t Display::background[RESOLUTION_Y][RESOLUTION_X];

u32string Display::ToU32String(string value) {
  wstring_convert<codecvt_utf8<char32_t>, char32_t> conv;
  return conv.from_bytes(value);
}

string Display::ToString(u32string value) {
  wstring_convert<codecvt_utf8<char32_t>, char32_t> conv;
  return conv.to_bytes(value);
}

void Display::Init() {
  for (size_t y = 0; y < RESOLUTION_Y; y++) {
    for (size_t x = 0; x < RESOLUTION_X; x++) {
      screenBuffer[x][y] = ' ';

      // if (x == 0) {
      //   if (y == 0) background[x][y] = U'\u250C';                     // ┌
      //   else if (y == RESOLUTION_Y - 1) background[x][y] = U'\u2514'; // └
      //   else if (y % 2 == 0) background[x][y] = U'\u2502';            // │
      //   else background[x][y] = U'\u251C';                            // ├
      // } else background[x][y] = U' ';
    }
  }
  for (int y = 0; y < RESOLUTION_Y; ++y) {
    for (int x = 0; x < RESOLUTION_X; ++x) {
      char32_t ch;

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
        ch = U' '; // inside cell
      }
      frameBuffer[x][y] = ch;
      background[x][y] = ch; // note: [y][x], not [x][y]
    }
  }



  wstring_convert<codecvt_utf8<char32_t>, char32_t> conv;
  for (size_t y = 0; y < RESOLUTION_Y; y++) {
    u32string line32;
    line32.reserve(RESOLUTION_X);
    for (size_t x = 0; x < RESOLUTION_X; x++) {
      line32.push_back(screenBuffer[x][y]);
    }

    // Convert whole line to UTF-8 and print
    string line8 = conv.to_bytes(line32);
    cout << line8 << '\n';
  }
}

void Display::Render() {


  Renderable &rend = Renderables::testRenderable();

  // cout << "From display x" << to_string(rend.position.x) << endl;
  // cout << "From display y" << to_string(rend.position.y) << endl;

  for (size_t sy = 0; sy < rend.sprite.height; sy++) {
    for (size_t sx = 0; sx < rend.sprite.width - 1; sx++) {
      int x = rend.position.x + sx;
      int y = rend.position.y + sy;
      frameBuffer[x][y] = rend.sprite.drawing[sy][sx];
    }
  }

  queue<Vector2> dirtyQueue;

  for (size_t y = 0; y < RESOLUTION_Y; y++) {
    for (size_t x = 0; x < RESOLUTION_X; x++) {
      if (screenBuffer[x][y] != frameBuffer[x][y]) {
        dirtyQueue.push(Vector2(x, y));
      };
    }
  }

  HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
  wstring_convert<codecvt_utf8<char32_t>, char32_t> conv;

  // if (dirtyQueue.size() != 0) cout << "Dirty count: " << dirtyQueue.size() << endl;


  while (!dirtyQueue.empty()) {
    Vector2 pos = dirtyQueue.front();
    dirtyQueue.pop();

    // cout << pos.x << "," << pos.y << endl;
    COORD consolePos = {static_cast<SHORT>(pos.x), static_cast<SHORT>(pos.y)};
    SetConsoleCursorPosition(h, consolePos);
    string character = conv.to_bytes(frameBuffer[static_cast<size_t>(pos.x)][static_cast<size_t>(pos.y)]);
    cout << character;
  }


  for (size_t y = 0; y < RESOLUTION_Y; y++) {
    for (size_t x = 0; x < RESOLUTION_X; x++) {
      screenBuffer[x][y] = frameBuffer[x][y];
      frameBuffer[x][y] = background[x][y];
    }
  }

  // TODO: Do stuff here
}
} // namespace Rendering
} // namespace Snake

