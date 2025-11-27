#include "data/Renderables/Renderables.h"
#include "iostream"
#include "rendering/Display/Display.h"
#include <chrono>
#include <windows.h>

bool travelingRight = true;

void tick(float dt) {
  Renderable &rend = Snake::Data::Renderables::testRenderable();
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
  // std::cout << rend.position.x << endl;
  // system("cls");
  Snake::Rendering::Display::Render();
}

int main() {

  SetConsoleOutputCP(CP_UTF8);
  // std::cout << "ASD";
  Snake::Rendering::Display::Init();
  Snake::Rendering::Display::Render();


  // Renderable &rend = Snake::Data::Renderables::testRenderable();
  // std::cout << rend.position.x << endl;
  // rend.position.x += 1;
  // std::cout << rend.position.x << endl;
  // return 0;

  auto last = std::chrono::high_resolution_clock::now();

  while (true) {
    auto now = std::chrono::high_resolution_clock::now();
    float dt = std::chrono::duration<float>(now - last).count();
    last = now;

    tick(dt);
  }
}
