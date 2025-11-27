#pragma once
#include "../Sprite/Sprite.h"
#include <string>

#define RESOLUTION_X 69
#define RESOLUTION_Y 45

namespace Snake {
namespace Rendering {
class Display {
private:
  static wchar_t screenBuffer[RESOLUTION_X][RESOLUTION_Y];
  static wchar_t frameBuffer[RESOLUTION_X][RESOLUTION_Y];
  static wchar_t background[RESOLUTION_X][RESOLUTION_Y];

public:
  static void Render();
  static void Init();
  // static string ToString(u32string value);
  // static u32string ToU32String(string value);
};
} // namespace Rendering
} // namespace Snake
