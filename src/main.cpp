#include "data/Renderables/Renderables.h"
#include "iostream"
#include "rendering/Display/Display.h"
#include <chrono>
#include <windows.h>

bool isTravelingRight = true;
int frameCount = 0;

void tick(float dt) {
  Renderable &rend = Snake::Data::Renderables::snakeHead;


  if (isTravelingRight) {
    if ((rend.position.x + 10 * dt + rend.sprite->width) <= RESOLUTION_X) rend.position.x += 10 * dt;
    else isTravelingRight = false;
  }

  if (!isTravelingRight) {
    if ((rend.position.x - 10 * dt) >= 0) rend.position.x -= 10 * dt;
    else isTravelingRight = true;
  }


  if (isTravelingRight && rend.sprite->id != Snake::Data::Sprites::head_right.id) rend.sprite = &Snake::Data::Sprites::head_right;
  if (!isTravelingRight && rend.sprite->id != Snake::Data::Sprites::head_left.id) rend.sprite = &Snake::Data::Sprites::head_left;


  Snake::Rendering::Display::Render();
  frameCount++;
}

int main() {
  Snake::Rendering::Display::Init();


  auto last = std::chrono::high_resolution_clock::now();

  while (true) {

    auto now = std::chrono::high_resolution_clock::now();
    float dt = std::chrono::duration<float>(now - last).count();
    last = now;
    tick(dt);
  }
}
