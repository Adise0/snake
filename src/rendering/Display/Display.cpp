#include "Display.h"
#include "../../data/Renderables/Renderables.h"
#include "iostream"
#include <codecvt>

using namespace std;
using namespace Snake::Data;

namespace Snake {
namespace Rendering {


char32_t Display::screenBuffer[RESOLUTION_Y][RESOLUTION_X];

u32string Display::ToU32String(string value) {
  wstring_convert<codecvt_utf8<char32_t>, char32_t> conv;
  return conv.from_bytes(value);
}

string Display::ToString(u32string value) {
  wstring_convert<codecvt_utf8<char32_t>, char32_t> conv;
  return conv.to_bytes(value);
}

void Display::Render() {

  for (size_t y = 0; y < RESOLUTION_Y; y++) {
    for (size_t x = 0; x < RESOLUTION_X; x++) {
      Display::screenBuffer[x][y] = ' ';
    }
  }

  Renderable rend = Renderables::testRenderable;

  for (size_t sy = 0; sy < rend.sprite.height; sy++) {
    for (size_t sx = 0; sx < rend.sprite.width; sx++) {
      int x = rend.position.x + sx;
      int y = rend.position.y + sy;
      screenBuffer[x][y] = rend.sprite.drawing[y][x];
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



  // TODO: Do stuff here
}
} // namespace Rendering
} // namespace Snake

