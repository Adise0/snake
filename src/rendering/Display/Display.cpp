#include "Display.h"
#include "iostream"
#include <codecvt>

using namespace std;
namespace Snake {
namespace Rendering {


u32string Display::screenBuffer[RESOLUTION_Y][RESOLUTION_X];

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
      Display::screenBuffer[y][x] = U"" + ToU32String(to_string(x)) + U" " + ToU32String(to_string(y));
    }
  }

  for (size_t y = 0; y < RESOLUTION_Y; y++) {
    for (size_t x = 0; x < RESOLUTION_X; x++) {
      cout << ToString(screenBuffer[y][x]) << " ";
    }
    cout << endl;
  }



  // TODO: Do stuff here
}
} // namespace Rendering
} // namespace Snake

