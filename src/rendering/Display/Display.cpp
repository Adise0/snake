#include "Display.h"
#include "../Sprite/Sprites.h"
#include <codecvt>
#include <iostream>

#define RESOLUTION_X 64
#define RESOLUTION_Y 60
#define MAP_X 17
#define MAP_Y 15


using namespace std;
namespace Snake {
namespace Rendering {

void Display::render() {

  //TEMP
  Sprite *spriteBuffer[MAP_X][MAP_Y];

  for (size_t y = 0; y < MAP_Y; y++) {
    for (size_t x = 0; x < MAP_X; x++) {

      Sprite *sprite1 = x % 2 == 0 ? &Sprites::background1 : &Sprites::background2;
      Sprite *sprite2 = x % 2 == 0 ? &Sprites::background2 : &Sprites::background1;
      spriteBuffer[x][y] = y % 2 == 0 ? sprite1 : sprite2;
    }
  }

  char32_t displayBuffer[RESOLUTION_X][RESOLUTION_Y];
  for (size_t y = 0; y < RESOLUTION_Y; ++y)
    for (size_t x = 0; x < RESOLUTION_X; ++x)
      displayBuffer[x][y] = ' ';

  // Construct sprite buffer
  for (size_t y = 0; y < MAP_Y; y++) {
    for (size_t x = 0; x < MAP_X; x++) {

      Sprite *sprite = spriteBuffer[x][y];
      vector<u32string> spriteData = sprite->GetStrings32();

      for (size_t sy = 0; sy < sprite->height; sy++) {
        for (size_t sx = 0; sx < sprite->width; sx++) {
          displayBuffer[x * sprite->width + sx][y * sprite->height + sy] = spriteData[sy][sx];
        }
      }
    }
  }

  cout << "asdasd" << endl;
  wstring_convert<codecvt_utf8<char32_t>, char32_t> conv;

  for (size_t y = 0; y < RESOLUTION_Y; y++) {
    u32string line32;
    line32.reserve(RESOLUTION_X);
    for (size_t x = 0; x < RESOLUTION_X; x++) {
      line32.push_back(displayBuffer[x][y]);
    }

    // Convert whole line to UTF-8 and print
    string line8 = conv.to_bytes(line32);
    cout << line8 << '\n';
  }
}

} // namespace Rendering
} // namespace Snake
