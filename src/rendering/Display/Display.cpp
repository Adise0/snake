#include "Display.h"
#include "../../GameManager/GameManager.h"
#include "../../data/Consts/Consts.h"
#include "../../data/Sprites/Sprites.h"
#include "../../objects/SpriteRenderer/SpriteRenderer.h"
#include <algorithm>
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

  HideCursor();

  PrintHeader();
  InitializeBackground();
  InitializeBuffers();

  FillBackground();
  // #endregion
}

void Display::HideCursor() {
  // #region HideCursor
  CONSOLE_CURSOR_INFO cursorInfo;
  GetConsoleCursorInfo(consoleHandle, &cursorInfo);

  cursorInfo.bVisible = FALSE;
  SetConsoleCursorInfo(consoleHandle, &cursorInfo);
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

  // std::cout << " Drawing: " << SpriteRenderer::spriteRenderers.size() << " sprites";



  for (SpriteRenderer *spriteRenderer : SpriteRenderer::spriteRenderers) {
    // std::cout << " - Should render: " << spriteRenderer->render << std::endl;
    if (!spriteRenderer->render) continue;

    int width = spriteRenderer->sprite->rect.x;
    int height = spriteRenderer->sprite->rect.y;

    int positionX = spriteRenderer->position.x;
    int positionY = spriteRenderer->position.y;

    std::vector<std::u32string> &characters = spriteRenderer->sprite->characters;

    for (size_t spriteY = 0; spriteY < height; spriteY++) {
      for (size_t spriteX = 0; spriteX < width; spriteX++) {

        if (characters[spriteY][spriteX] == ' ') continue;

        int x = positionX + spriteX;
        int y = positionY + spriteY;
        if (x < 0 || x >= Consts::RESOLUTION_X || y < 0 || y >= Consts::RESOLUTION_Y) continue;

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
  while (!dirtyChars.empty()) {
    Vector2 pos = dirtyChars.front();
    dirtyChars.pop();

    short x = pos.x;
    short y = pos.y;

    COORD consolePos = {x, y + Consts::TOP_OFFSET};
    SetConsoleCursorPosition(consoleHandle, consolePos);

    std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> conv;
    std::string converted = conv.to_bytes(screenBuffer[x][y]);
    std::cout << converted;

    std::string applesString = "Apples: " + std::to_string(GameManager::apples);
    consolePos = {5, (short)(Consts::TOP_OFFSET / 2)};
    SetConsoleCursorPosition(consoleHandle, consolePos);
    std::cout << applesString;


    std::string pointsString = "Points: " + std::to_string(GameManager::points);
    consolePos = {(short)(Consts::RESOLUTION_X - 5 - pointsString.length()),
                  (short)(Consts::TOP_OFFSET / 2)};
    SetConsoleCursorPosition(consoleHandle, consolePos);
    std::cout << pointsString;
  }
  // #endregion
}

void Display::PrintHeader() {


  std::u32string topSegment = U"";
  std::u32string otherSegments = U"";

  for (size_t i = 0; i < Consts::RESOLUTION_X - 2; i++) {
    topSegment += U"\u2500";
    otherSegments += U" ";
  }

  std::u32string topLine = U"\u250C" + topSegment + U"\u2510";
  std::u32string otherLine = U"\u2502" + otherSegments + U"\u2502";

  COORD consolePos = {0, 0};
  SetConsoleCursorPosition(consoleHandle, consolePos);

  std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> conv;
  std::string topLineConverted = conv.to_bytes(topLine);
  std::string lineConverted = conv.to_bytes(otherLine);

  std::cout << topLineConverted << std::endl;
  for (size_t i = 0; i < Consts::TOP_OFFSET * Consts::CELL_RESOLUTION_Y; i++) {
    std::cout << lineConverted << std::endl;
  }
}

void Display::ShowGameOver() {

  std::string gameOverString = "Game Over!";

  short x = Consts::RESOLUTION_X / 2 - (gameOverString.length() / 2) - 5;
  short y = (Consts::TOP_OFFSET) + (Consts::RESOLUTION_Y / 2) - 2;

  for (size_t row = 0; row < gameOverString.length() + 10; row++) {
    for (size_t col = 0; col < 5; col++) {
      short sprX = x + row;
      short sprY = y + col;

      COORD consolePos = {sprX, sprY};
      SetConsoleCursorPosition(consoleHandle, consolePos);
      std::cout << " ";
    }
  }


  COORD consolePos = {x + 5, y + 2};
  SetConsoleCursorPosition(consoleHandle, consolePos);
  std::cout << gameOverString;
}

} // namespace Snake::Rendering
