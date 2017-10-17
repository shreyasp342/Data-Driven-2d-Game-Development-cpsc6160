#include <iostream>
#include <SDL2/SDL.h>
#include "frameGenerator.h"
#include "draw.h"

const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 480;
const std::string TITLE = "BiCycle";

int main(void) {
  SDL_Renderer *renderer=nullptr;
  SDL_Window *window=nullptr;

  Draw cycle(renderer, window, WINDOW_WIDTH, WINDOW_HEIGHT, TITLE);
  SDL_Color color = {0, 0, 255,255};
  std::cout << cycle << "\n";
  cycle.drawCycle(color);
  cycle.genFrame();

  SDL_Event event;
  const Uint8* keystate;
  while ( true ) {
    keystate = SDL_GetKeyboardState(0);
    if (keystate[SDL_SCANCODE_ESCAPE]) { break; }
    if (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
        break;
      }
    }
  }
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
  return EXIT_SUCCESS;
}
