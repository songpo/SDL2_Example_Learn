//
// Created by liuso on 2022/1/1.
//

#define SDL_MAIN_HANDLED

#include <SDL.h>
#include <string>
#include <SDL_image.h>

const char *WINDOW_TITLE = "SDL Example";

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

// The window we'll be rendering to
SDL_Window *gWindow = nullptr;

// The surface contained by the window
SDL_Surface *gScreenSurface = nullptr;

// Current displayed image
SDL_Surface *gCurrentSurface = nullptr;

// Current stretched surface
SDL_Surface *gStretchedSurface;

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
    // Initialize PNG loading
    int imageFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imageFlags) & imageFlags)) {
      SDL_Log("SDL_image could not initialize! SDL_Error: %s", IMG_GetError());
      success = false;
    } else {
      // Get window surface
      gScreenSurface = SDL_GetWindowSurface(gWindow);
    }
  }

  return success;
}

// Load individual image
SDL_Surface *loadSurface(std::string filepath) {
  // The final optimized image
  SDL_Surface *optimizedSurface = nullptr;

  // Load image at specified path
  SDL_Surface *loadedSurface = IMG_Load(filepath.c_str());
  if (loadedSurface == nullptr) {
    SDL_Log("Unable to load image %s! SDL_Error: %s", filepath.c_str(), SDL_GetError());
  } else {
    // Convert surface to screen format
    optimizedSurface = SDL_ConvertSurface(loadedSurface, gScreenSurface->format, 0);
    if (optimizedSurface == nullptr) {
      SDL_Log("Unable to optimize image %s! SDL_Error: %s", filepath.c_str(), SDL_GetError());
    }

    // Get rid of old loaded surface
    SDL_FreeSurface(loadedSurface);
  }

  return optimizedSurface;
}

// Load media
bool loadMedia() {
  // Loading success flag
  bool success = true;

  // Load default surface
  gStretchedSurface = loadSurface("gfx/loaded.png");
  if (gStretchedSurface == nullptr) {
    SDL_Log("Failed to load surface");
    success = false;
  }

  return success;
}

// Free media and shutdown SDL
void close() {
  // Free surface
  SDL_FreeSurface(gStretchedSurface);

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

        // Apply the image stretched
        SDL_Rect stretchRect;
        stretchRect.x = 0;
        stretchRect.y = 0;
        stretchRect.w = SCREEN_WIDTH;
        stretchRect.h = SCREEN_HEIGHT;
        SDL_BlitScaled(gStretchedSurface, nullptr, gScreenSurface, &stretchRect);

        // Update the surface
        SDL_UpdateWindowSurface(gWindow);
      }
    }
  }

  // Free resources and close SDL
  close();

  return 0;
}