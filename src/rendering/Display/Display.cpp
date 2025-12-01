#include "Display.h"
#include "../../data/Consts/Consts.h"
#include "../../objects/SpriteRenderer/SpriteRenderer.h"
#include <codecvt>
#include <iostream>



using namespace Snake::Data;
using namespace Snake::Objects;

namespace Snake::Rendering {
// #region Data
HANDLE Display::consoleHandle;
char32_t Display::background[Consts::RESOLUTION_X][Consts::RESOLUTION_Y];
char32_t Display::frameBuffer[Consts::RESOLUTION_X][Consts::RESOLUTION_Y];
char32_t Display::screenBuffer[Consts::RESOLUTION_X][Consts::RESOLUTION_Y];
std::queue<Vector2> Display::dirtyChars;
// #endregion

void Display::Initialize() {
  // #region Initialize
  consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);

  InitializeBackground();
  InitializeBuffers();

  FillBackground();
  // #endregion
}

void Display::InitializeBackground() {
  // #region InitializeBackground
  for (size_t y = 0; y < Consts::RESOLUTION_Y; y++) {
    for (size_t x = 0; x < Consts::RESOLUTION_X; x++) {
      wchar_t ch;

      bool top = (y == 0);
      bool bottom = (y == Consts::RESOLUTION_Y - 1);
      bool left = (x == 0);
      bool right = (x == Consts::RESOLUTION_X - 1);

      bool gridRow = y % 2 == 0;
      bool gridCol = x % 5 == 0;

      if (top && left) {
        ch = U'\u250C'; // ┌
      } else if (top && right) {
        ch = U'\u2510'; // ┐
      } else if (bottom && left) {
        ch = U'\u2514'; // └
      } else if (bottom && right) {
        ch = U'\u2518'; // ┘
      } else if (top && gridCol) {
        ch = U'\u252C'; // ┬ (top T)
      } else if (bottom && gridCol) {
        ch = U'\u2534'; // ┴ (bottom T)
      } else if (left && gridRow) {
        ch = U'\u251C'; // ├ (left T)
      } else if (right && gridRow) {
        ch = U'\u2524'; // ┤ (right T)
      } else if (gridRow && gridCol) {
        ch = U'\u253C'; // ┼ (cross)
      } else if (gridRow) {
        ch = U'\u2500'; // ─ (horizontal)
      } else if (gridCol) {
        ch = U'\u2502'; // │ (vertical)
      } else {
        ch = U' '; // inside cell
      }
      background[x][y] = ch;
    }
  }
  // #endregion
}

void Display::InitializeBuffers() {
  // #region InitializeBuffers
  for (size_t y = 0; y < Consts::RESOLUTION_Y; y++) {
    for (size_t x = 0; x < Consts::RESOLUTION_X; x++) {
      frameBuffer[x][y] = U' ';
      screenBuffer[x][y] = U' ';
    }
  }
  // #endregion
}

void Display::Tick() {
  // #region Tick
  FillBackground();
  DrawSprites();
  ComputeDirtyChars();
  Print();
  // #endregion
}

void Display::FillBackground() {
  // #region FillBackground
  for (size_t y = 0; y < Consts::RESOLUTION_Y; y++) {
    for (size_t x = 0; x < Consts::RESOLUTION_X; x++) {
      frameBuffer[x][y] = background[x][y];
    }
  }
  // #endregion
}

void Display::DrawSprites() {
  // #region DrawSprites
  for (SpriteRenderer *spriteRenderer : SpriteRenderer::spriteRenderers) {
    if (!spriteRenderer->render) continue;

    int width = spriteRenderer->sprite->rect.x;
    int height = spriteRenderer->sprite->rect.y;

    int positionX = spriteRenderer->position.x;
    int positionY = spriteRenderer->position.y;


    COORD consolePos = {0, 0};
    SetConsoleCursorPosition(consoleHandle, consolePos);
    std::cout << "Width: " << width << " Height: " << height << " Expected: " << width * height
              << std::endl;

    std::vector<std::u32string> &characters = spriteRenderer->sprite->characters;

    for (size_t spriteY = 0; spriteY < height; spriteY++) {
      for (size_t spriteX = 0; spriteX < width; spriteX++) {

        if (characters[spriteY][spriteX] == ' ') continue;

        int x = positionX + spriteX;
        int y = positionY + spriteY;


        if (characters[spriteY][spriteX] == 'b') {
          frameBuffer[x][y] = ' ';
          continue;
        }

        frameBuffer[x][y] = characters[spriteY][spriteX];
      }
    }
  }
  // #endregion
}

void Display::ComputeDirtyChars() {
  // #region ComputeDirtyChars
  for (size_t y = 0; y < Consts::RESOLUTION_Y; y++) {
    for (size_t x = 0; x < Consts::RESOLUTION_X; x++) {

      if (screenBuffer[x][y] == frameBuffer[x][y]) continue;

      screenBuffer[x][y] = frameBuffer[x][y];
      dirtyChars.push(Vector2(x, y));
    }
  }
  // #endregion
}

void Display::Print() {
  // #region Print
  COORD consolePos = {0, 1};
  SetConsoleCursorPosition(consoleHandle, consolePos);
  std::cout << "Chars to re-render: " << dirtyChars.size() << std::endl;

  while (!dirtyChars.empty()) {
    Vector2 pos = dirtyChars.front();
    dirtyChars.pop();

    short x = pos.x;
    short y = pos.y;

    COORD consolePos = {x, y + 2};
    SetConsoleCursorPosition(consoleHandle, consolePos);

    std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> conv;
    std::string converted = conv.to_bytes(screenBuffer[x][y]);
    std::cout << converted;
  }
  // #endregion
}

} // namespace Snake::Rendering
