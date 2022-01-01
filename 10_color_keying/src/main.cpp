//
// Created by liuso on 2022/1/1.
//

#define SDL_MAIN_HANDLED

#include <string>
#include <SDL.h>
#include <SDL_image.h>

#include "texture_mananger.h"

const char *WINDOW_TITLE = "SDL Example";

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

// The window we'll be rendering to
SDL_Window *gWindow = nullptr;

// The window renderer
SDL_Renderer *gRenderer = nullptr;

// The texture
LTexture gFooTexture;
LTexture gBackgroundTexture;

// Start up SDL and create window
bool init() {
  // Initialization flag
  bool success = true;

  // Init SDL
  if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
    SDL_Log("SDL could not initialize! SDL_Error: %s", SDL_GetError());
    success = false;
  }

  // Create window
  gWindow = SDL_CreateWindow(WINDOW_TITLE,
                             SDL_WINDOWPOS_CENTERED,
                             SDL_WINDOWPOS_CENTERED,
                             SCREEN_WIDTH,
                             SCREEN_HEIGHT,
                             SDL_WINDOW_SHOWN);
  if (gWindow == nullptr) {
    SDL_Log("Window could not be created! SDL_Error: %s", SDL_GetError());
    success = false;
  } else {
    // Create renderer for windows
    gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (gRenderer == nullptr) {
      SDL_Log("Create renderer failed! SDL_Error: %s", IMG_GetError());
      success = false;
    }
  }

  return success;
}

// Load media
bool loadMedia() {
  // Loading success flag
  bool success = true;

  // Load Foo' texture
  if (!gFooTexture.loadFromFile(gRenderer, "gfx/foo.png")) {
    SDL_Log("Failed to load Foo' texture image");
    success = false;
  }

  // Load Foo' texture
  if (!gBackgroundTexture.loadFromFile(gRenderer, "gfx/background.png")) {
    SDL_Log("Failed to load Background' texture image");
    success = false;
  }

  return success;
}

// Free media and shutdown SDL
void close() {
  // Free loaded images
  gFooTexture.free();
  gBackgroundTexture.free();

  // Destroy window
  SDL_DestroyWindow(gWindow);
  gWindow = nullptr;

  // Quit SDL_image
  IMG_Quit();

  // Quit SDL subsystem
  SDL_Quit();
}

int main(int argc, char *argv[]) {
  // Start up SDL and create window
  if (!init()) {
    SDL_Log("Failed to initialize!");
  } else {
    if (loadMedia()) {
      // Main loop flag
      bool quite = false;

      // Event handler
      SDL_Event event;

      // While application is running
      while (!quite) {
        // Handle events on queue
        while (SDL_PollEvent(&event)) {
          // User requests quit
          if (event.type == SDL_QUIT) {
            quite = true;
          }
        }

        // Clear screen
        SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(gRenderer);

        // Render texture to screen
        gBackgroundTexture.render(gRenderer, 0, 0);
        gFooTexture.render(gRenderer, 240, 190);

        // Update screen
        SDL_RenderPresent(gRenderer);
      }
    }
  }

  // Free resources and close SDL
  close();

  return 0;
}