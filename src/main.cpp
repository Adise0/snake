#include "iostream"
#include "objects/SpriteRenderer/SpriteRenderer.h"
#include "rendering/Config/Config.h"
#include "rendering/Display/Display.h"


using namespace Snake::Rendering;

int main() {
  Config::ConfigureConsole();
  Display::Initialize();

  Sprite sprite = Sprite(std::vector<std::u32string>{U"  ##  ", U"######", U"##  ##"});
  SpriteRenderer renderer = SpriteRenderer(Vector2(10, 10), &sprite);

  Display::Tick();


  return 0;
}
