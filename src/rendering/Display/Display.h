#pragma once
#include "../Sprite/Sprite.h"
#include <string>

#define RESOLUTION_X 68
#define RESOLUTION_Y 60

namespace Snake {
namespace Rendering {
class Display {
private:
  static char32_t screenBuffer[RESOLUTION_Y][RESOLUTION_X];
  static char32_t frameBuffer[RESOLUTION_Y][RESOLUTION_X];
  static char32_t background[RESOLUTION_Y][RESOLUTION_X];

public:
  static void Render();
  static void Init();
  static string ToString(u32string value);
  static u32string ToU32String(string value);
};
} // namespace Rendering
} // namespace Snake
