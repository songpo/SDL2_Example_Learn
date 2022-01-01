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

// Scene sprites
LTexture gModulatedTexture;

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
  if (!gModulatedTexture.loadFromFile(gRenderer, "gfx/colors.png")) {
    SDL_Log("Failed to load texture image");
    success = false;
  } else {

  }

  return success;
}

// Free media and shutdown SDL
void close() {
  // Free loaded images
  gModulatedTexture.free();

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

      // Modulation components
      Uint8 r = 255;
      Uint8 g = 255;
      Uint8 b = 255;

      // While application is running
      while (!quite) {
        // Handle events on queue
        while (SDL_PollEvent(&event)) {
          // User requests quit
          if (event.type == SDL_QUIT) {
            quite = true;
          } else {
            // On keypress change rgb values
            switch (event.key.keysym.sym) {
              case SDLK_q: r += 5;
                break;
              case SDLK_w: g += 5;
                break;
              case SDLK_e: b += 5;
                break;
              case SDLK_a: r -= 5;
                break;
              case SDLK_s: g -= 5;
                break;
              case SDLK_d: b -= 5;
                break;
            }
          }
        }

        // Clear screen
        SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(gRenderer);

        // Render sprite
        gModulatedTexture.setColor(r, g, b);
        gModulatedTexture.render(gRenderer, 0, 0);

        // Update screen
        SDL_RenderPresent(gRenderer);
      }
    }
  }

  // Free resources and close SDL
  close();

  return 0;
}