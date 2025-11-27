#include "Display.h"
#include "../../data/Renderables/Renderables.h"
#include "iostream"
#include <codecvt>
#include <windows.h>

using namespace std;
using namespace Snake::Data;

namespace Snake {
namespace Rendering {


char32_t Display::screenBuffer[RESOLUTION_Y][RESOLUTION_X];
char32_t Display::frameBuffer[RESOLUTION_Y][RESOLUTION_X];

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
      frameBuffer[x][y] = '0';
      screenBuffer[x][y] = '@';
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

  bool dirty[RESOLUTION_Y][RESOLUTION_X];

  for (size_t y = 0; y < RESOLUTION_Y; y++) {
    for (size_t x = 0; x < RESOLUTION_X; x++) {
      if (screenBuffer[x][y] != frameBuffer[x][y]) {
        dirty[x][y] = true;
      };
    }
  }

  HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
  wstring_convert<codecvt_utf8<char32_t>, char32_t> conv;

  for (size_t y = 0; y < RESOLUTION_Y; y++) {
    for (size_t x = 0; x < RESOLUTION_X; x++) {
      if (dirty[x][y]) {
        COORD pos = {x, y};
        SetConsoleCursorPosition(h, pos);
        // string character = conv.to_bytes(frameBuffer[x][y]);

        cout << "x";
      };
    }
  }

  // cout << "Rendering" << endl;
  // wstring_convert<codecvt_utf8<char32_t>, char32_t> conv;
  // for (size_t y = 0; y < RESOLUTION_Y; y++) {
  //   u32string line32;
  //   line32.reserve(RESOLUTION_X);
  //   for (size_t x = 0; x < RESOLUTION_X; x++) {
  //     line32.push_back(screenBuffer[x][y]);
  //   }

  //   // Convert whole line to UTF-8 and print
  //   string line8 = conv.to_bytes(line32);
  //   cout << line8 << '\n';
  // }
  // cout << "End" << endl;

  for (size_t y = 0; y < RESOLUTION_Y; y++) {
    for (size_t x = 0; x < RESOLUTION_X; x++) {
      screenBuffer[x][y] = frameBuffer[x][y];
    }
  }

  // TODO: Do stuff here
}
} // namespace Rendering
} // namespace Snake

