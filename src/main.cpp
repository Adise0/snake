#include "data/Renderables/Renderables.h"
#include "iostream"
#include "rendering/Display/Display.h"
#include <chrono>
#include <windows.h>

bool travelingRight = true;
int frameCount = 0;

void tick(float dt) {
  Renderable &rend = Snake::Data::Renderables::snakeHead;
  // cout << to_string(dt) << endl;


  if (travelingRight == true && rend.position.x + 10 * dt + rend.sprite.width <= RESOLUTION_X) {
    rend.position.x += 10 * dt;
  } else {
    travelingRight = false;
  }

  if (!travelingRight == true && rend.position.x - 10 * dt >= 0) {
    rend.position.x -= 10 * dt;
  } else {
    travelingRight = true;
  }


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
