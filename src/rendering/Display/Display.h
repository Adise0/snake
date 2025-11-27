#pragma once
#include "../../objects/Vector2/Vector2.h"
#include "../Sprite/Sprite.h"
#include <queue>
#include <string>

#define RESOLUTION_X 69
#define RESOLUTION_Y 45

using namespace Snake::Objects;

namespace Snake {
namespace Rendering {
class Display {
private:
  static wchar_t screenBuffer[RESOLUTION_X][RESOLUTION_Y];
  static wchar_t frameBuffer[RESOLUTION_X][RESOLUTION_Y];
  static wchar_t background[RESOLUTION_X][RESOLUTION_Y];
  static queue<Vector2> dirtyChars;

public:
  static void Render();
  static void Init();
  // static string ToString(u32string value);
  // static u32string ToU32String(string value);
};
} // namespace Rendering
} // namespace Snake
