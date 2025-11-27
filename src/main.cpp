#include "data/Renderables/Renderables.h"
#include "iostream"
#include "rendering/Display/Display.h"
#include <chrono>
#include <windows.h>

void tick(float dt) {
  Renderable &rend = Snake::Data::Renderables::testRenderable();
  // cout << to_string(dt) << endl;

  rend.position.x += 10 * dt;
  // std::cout << rend.position.x << endl;
  // system("cls");
  // Snake::Rendering::Display::Render();
}

int main() {

  SetConsoleOutputCP(CP_UTF8);
  // std::cout << "ASD";
  Snake::Rendering::Display::Init();
  Snake::Rendering::Display::Render();


  Renderable &rend = Snake::Data::Renderables::testRenderable();
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
