//
// Created by liuso on 2022/1/1.
//

#define SDL_MAIN_HANDLED

#include <SDL.h>
#include <string>

const char *WINDOW_TITLE = "SDL Example";

const int SCREEN_WIDTH = 1920;
const int SCREEN_HEIGHT = 1080;

// The window we'll be rendering to
SDL_Window *gWindow = nullptr;

// The surface contained by the window
SDL_Surface *gScreenSurface = nullptr;

SDL_Surface *gHelloWorld = nullptr;

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
  }

  // Get window surface
  gScreenSurface = SDL_GetWindowSurface(gWindow);

  return success;
}

// Load media
bool loadMedia() {
  // Loading success flag
  bool success = true;

  // Load splash image
  std::string filepath = "gfx/hello_world.bmp";
  gHelloWorld = SDL_LoadBMP(filepath.c_str());
  if (gHelloWorld == nullptr) {
    SDL_Log("Unable to load image %s! SDL_Error: %s", filepath.c_str(), SDL_GetError());
    success = false;
  }

  return success;
}

// Free media and shutdown SDL
void close() {
  // Deallocate surface
  SDL_FreeSurface(gHelloWorld);
  gHelloWorld = nullptr;

  // Destroy window
  SDL_DestroyWindow(gWindow);
  gWindow = nullptr;

  // Quit SDL subsystem
  SDL_Quit();
}

int main(int argc, char *argv[]) {
  // Start up SDL and create window
  if (!init()) {
    SDL_Log("Failed to initialize!");
  } else {
    // Load media
    if (!loadMedia()) {
      SDL_Log("Failed to load media!");
    } else {
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

        // Apply the image
        SDL_BlitSurface(gHelloWorld, nullptr, gScreenSurface, nullptr);

        // Update the surface
        SDL_UpdateWindowSurface(gWindow);
      }
    }
  }

  // Free resources and close SDL
  close();

  return 0;
}