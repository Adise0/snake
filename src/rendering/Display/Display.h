#pragma once
#include "../../data/Consts/Consts.h"
#include "../../objects/Vector2/Vector2.h"
#include <queue>
#include <windows.h>


using namespace Snake::Data;
using namespace Snake::Objects;

namespace Snake::Rendering {

class Display {
private:
  /// @brief The background static buffer
  static char32_t background[Consts::RESOLUTION_X][Consts::RESOLUTION_Y];
  /// @brief The current frame buffer (memory only)
  static char32_t frameBuffer[Consts::RESOLUTION_X][Consts::RESOLUTION_Y];
  /// @brief The current screen buffer (holds the rendered and to render values)
  static char32_t screenBuffer[Consts::RESOLUTION_X][Consts::RESOLUTION_Y];
  /// @brief The queue of scren positions to re-draw
  static std::queue<Vector2> dirtyChars;

public:
  /// @brief The console handle
  static HANDLE consoleHandle;

private:
  /// @brief Hides the console cursor
  static void HideCursor();

  /// @brief Initializes the background buffer
  static void InitializeBackground();

  /// @brief Initializes the screen buffers
  static void InitializeBuffers();

  /// @brief Fills the frame buffer with the background values
  static void FillBackground();

  /// @brief Draws the sprite list into the frame buffer
  static void DrawSprites();

  /// @brief Computes the characcters that changed and adds them to the dirty queue
  static void ComputeDirtyChars();

  /// @brief Prints the current dirty chars
  static void Print();


public: /// @brief Initializes the renderer
  static void Initialize();
  /// @brief Ticks the display
  static void Tick();
};
} // namespace Snake::Rendering
