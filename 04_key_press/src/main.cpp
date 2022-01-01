//
// Created by liuso on 2022/1/1.
//

#define SDL_MAIN_HANDLED

#include <SDL.h>
#include <string>

// Key press surfaces constants
enum KeyPressSurfaces {
  KEY_PRESS_SURFACE_DEFAULT,
  KEY_PRESS_SURFACE_UP,
  KEY_PRESS_SURFACE_DOWN,
  KEY_PRESS_SURFACE_LEFT,
  KEY_PRESS_SURFACE_RIGHT,
  KEY_PRESS_SURFACE_TOTAL
};

const char *WINDOW_TITLE = "SDL Example";

const int SCREEN_WIDTH = 1920;
const int SCREEN_HEIGHT = 1080;

// The window we'll be rendering to
SDL_Window *gWindow = nullptr;

// The surface contained by the window
SDL_Surface *gScreenSurface = nullptr;

// The images that correspond to a keypress
SDL_Surface *gKeyPressSurfaces[KEY_PRESS_SURFACE_TOTAL];

// Current displayed image
SDL_Surface *gCurrentSurface = nullptr;

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
  if (gWindow == NULL) {
    SDL_Log("Window could not be created! SDL_Error: %s", SDL_GetError());
    success = false;
  }

  // Get window surface
  gScreenSurface = SDL_GetWindowSurface(gWindow);

  return success;
}

// Load individual image
SDL_Surface *loadSurface(std::string filepath) {
  // Load image at specified path
  SDL_Surface *loadedSurface = SDL_LoadBMP(filepath.c_str());
  if (loadedSurface == nullptr) {
    SDL_Log("Unable to load image %s! SDL_Error: %s", filepath.c_str(), SDL_GetError());
  }

  return loadedSurface;
}

// Load media
bool loadMedia() {
  // Loading success flag
  bool success = true;

  // Load default surface
  gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT] = loadSurface("gfx/press.bmp");
  if (gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT] == nullptr) {
    SDL_Log("Failed to load default image! SDL_Error: %s", SDL_GetError());
    success = false;
  }

  // Load up surface
  gKeyPressSurfaces[KEY_PRESS_SURFACE_UP] = loadSurface("gfx/up.bmp");
  if (gKeyPressSurfaces[KEY_PRESS_SURFACE_UP] == nullptr) {
    SDL_Log("Failed to load up image! SDL_Error: %s", SDL_GetError());
    success = false;
  }

  // Load down surface
  gKeyPressSurfaces[KEY_PRESS_SURFACE_DOWN] = loadSurface("gfx/down.bmp");
  if (gKeyPressSurfaces[KEY_PRESS_SURFACE_DOWN] == nullptr) {
    SDL_Log("Failed to load down image! SDL_Error: %s", SDL_GetError());
    success = false;
  }

  // Load left surface
  gKeyPressSurfaces[KEY_PRESS_SURFACE_LEFT] = loadSurface("gfx/left.bmp");
  if (gKeyPressSurfaces[KEY_PRESS_SURFACE_LEFT] == nullptr) {
    SDL_Log("Failed to load left image! SDL_Error: %s", SDL_GetError());
    success = false;
  }

  // Load right surface
  gKeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT] = loadSurface("gfx/right.bmp");
  if (gKeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT] == nullptr) {
    SDL_Log("Failed to load right image! SDL_Error: %s", SDL_GetError());
    success = false;
  }

  return success;
}

// Free media and shutdown SDL
void close() {
  // Deallocate surface
  for (auto &it: gKeyPressSurfaces) {
    SDL_FreeSurface(it);
    it = nullptr;
  }

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

      // Set default current surface
      gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT];

      // While application is running
      while (!quite) {
        // Handle events on queue
        while (SDL_PollEvent(&event)) {
          // User requests quit
          if (event.type == SDL_QUIT) {
            quite = true;
          } else {
            // Select surfaces based on key press
            switch (event.key.keysym.sym) {
              case SDLK_UP:gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_UP];
                break;
              case SDLK_DOWN:gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_DOWN];
                break;
              case SDLK_LEFT:gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_LEFT];
                break;
              case SDLK_RIGHT:gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT];
                break;
              default:gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT];
                break;
            }
          }
        }

        // Apply the image
        SDL_BlitSurface(gCurrentSurface, nullptr, gScreenSurface, nullptr);

        // Update the surface
        SDL_UpdateWindowSurface(gWindow);
      }
    }
  }

  // Free resources and close SDL
  close();

  return 0;
}