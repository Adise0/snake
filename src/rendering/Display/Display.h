#pragma once
#include "../Sprite/Sprite.h"
#include <string>

#define RESOLUTION_X 68
#define RESOLUTION_Y 60

namespace Snake {
namespace Rendering {
class Display {
private:
  static u32string screenBuffer[RESOLUTION_Y][RESOLUTION_X];

public:
  static void Render();
  static string ToString(u32string value);
  static u32string ToU32String(string value);
};
} // namespace Rendering
} // namespace Snake
