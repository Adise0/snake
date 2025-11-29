#include <SDL3/SDL.h>
#include <iostream>
#include <windows.h>

int main(int argc, char *argv[]) {
  // Initialize SDL video subsystem
  if (!SDL_Init(SDL_INIT_VIDEO)) {
    std::cerr << "SDL_Init failed: " << SDL_GetError() << std::endl;
    return 1;
  }

  // Create a window
  SDL_Window *window = SDL_CreateWindow("Snake", // window title
                                        800,     // width
                                        600,     // height
                                        0        // flags (or 0 for default)
  );

  if (!window) {
    std::cerr << "SDL_CreateWindow failed: " << SDL_GetError() << std::endl;
    SDL_Quit();
    return 1;
  }

  // Create a renderer (for drawing)
  SDL_Renderer *renderer = SDL_CreateRenderer(window, nullptr);
  if (!renderer) {
    std::cerr << "SDL_CreateRenderer failed: " << SDL_GetError() << std::endl;
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 1;
  }
  bool running = true;
  SDL_Event event;

  while (running) {
    // Handle all pending events
    while (SDL_PollEvent(&event)) {
      switch (event.type) {
      case SDL_EVENT_QUIT:
        running = false;
        break;

      case SDL_EVENT_KEY_DOWN:
        // Escape closes the window
        if (event.key.key == SDLK_ESCAPE) {
          running = false;
        }
        break;

      default:
        break;
      }
    }

    // Clear screen with a color
    SDL_SetRenderDrawColor(renderer, 0, 40, 80, 255); // RGBA
    SDL_RenderClear(renderer);

    // Draw stuff here later...

    // Show what we rendered
    SDL_RenderPresent(renderer);
  }

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
  return 0;
}

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) { return main(__argc, __argv); }

