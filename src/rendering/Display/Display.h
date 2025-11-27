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
  void Render();
};
} // namespace Rendering
} // namespace Snake
