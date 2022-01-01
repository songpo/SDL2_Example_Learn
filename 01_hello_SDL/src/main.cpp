//
// Created by liuso on 2022/1/1.
//

#define SDL_MAIN_HANDLED

#include <SDL.h>

const char *WINDOW_TITLE = "SDL Example";
const int SCREEN_WIDTH = 1920;
const int SCREEN_HEIGHT = 1080;

int main(int argc, char *argv[]) {
  // The window we'll be rendering to
  SDL_Window *window = NULL;

  // The surface contained by the window
  SDL_Surface *screenSurface = NULL;

  // Init SDL
  if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
    SDL_Log("SDL could not initialize! SDL_Error: %s", SDL_GetError());
    return 1;
  }

  // Create window
  window = SDL_CreateWindow(WINDOW_TITLE,
                            SDL_WINDOWPOS_CENTERED,
                            SDL_WINDOWPOS_CENTERED,
                            SCREEN_WIDTH,
                            SCREEN_HEIGHT,
                            SDL_WINDOW_SHOWN);
  if (window == NULL) {
    SDL_Log("Window could not be created! SDL_Error: %s", SDL_GetError());
    return 2;
  }

  // Get window surface
  screenSurface = SDL_GetWindowSurface(window);

  // Fill the surface white
  uint32_t color = SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF);
  SDL_FillRect(screenSurface, NULL, color);

  // Update the surface
  SDL_UpdateWindowSurface(window);

  // Wait two seconds
  SDL_Delay(2000);

  // Destroy window
  SDL_DestroyWindow(window);

  // Quit SDL subsystems
  SDL_Quit();

  return 0;
}