//
// Created by liuso on 2022/1/1.
//

#define SDL_MAIN_HANDLED

#include <string>
#include <SDL.h>
#include <SDL_image.h>

const char *WINDOW_TITLE = "SDL Example";

const int SCREEN_WIDTH = 1920;
const int SCREEN_HEIGHT = 1080;

// The window we'll be rendering to
SDL_Window *gWindow = nullptr;

// The window renderer
SDL_Renderer *gRenderer = nullptr;

// The texture
SDL_Texture *gTexture = nullptr;

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

// Load texture
SDL_Texture *loadTexture(std::string filepath) {
  // The final texture
  SDL_Texture *newTexture = nullptr;

  // Load image at specified path
  SDL_Surface *loadedSurface = IMG_Load(filepath.c_str());
  if (loadedSurface == nullptr) {
    SDL_Log("Unable to load image %s! SDL_Error: %s", filepath.c_str(), SDL_GetError());
  } else {
    newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
    if (newTexture == nullptr) {
      SDL_Log("Unable to load texture %s! SDL_Error: %s", filepath.c_str(), SDL_GetError());
    }

    // Get rid of old loaded surface
    SDL_FreeSurface(loadedSurface);
  }

  return newTexture;
}

// Load media
bool loadMedia() {
  // Loading success flag
  bool success = true;

  gTexture = loadTexture("gfx/viewport.png");
  if (gTexture == nullptr) {
    success = false;
  }

  return success;
}

// Free media and shutdown SDL
void close() {
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
        SDL_RenderClear(gRenderer);

        // Top left corner viewport
        SDL_Rect topLeftViewport;
        topLeftViewport.x = 0;
        topLeftViewport.y = 0;
        topLeftViewport.w = SCREEN_WIDTH / 2 - 5;
        topLeftViewport.h = SCREEN_HEIGHT / 2;
        SDL_RenderSetViewport(gRenderer, &topLeftViewport);

        // Render texture to screen
        SDL_RenderCopy(gRenderer, gTexture, nullptr, nullptr);

        // TopRight corner viewport
        SDL_Rect topRightViewport;
        topRightViewport.x = SCREEN_WIDTH / 2 + 5;
        topRightViewport.y = 0;
        topRightViewport.w = SCREEN_WIDTH / 2;
        topRightViewport.h = SCREEN_HEIGHT / 2;
        SDL_RenderSetViewport(gRenderer, &topRightViewport);

        // Render texture to screen
        SDL_RenderCopy(gRenderer, gTexture, nullptr, nullptr);

        // TopRight corner viewport
        SDL_Rect bottomViewport;
        bottomViewport.x = 0;
        bottomViewport.y = SCREEN_HEIGHT / 2 + 10;
        bottomViewport.w = SCREEN_WIDTH;
        bottomViewport.h = SCREEN_HEIGHT / 2 - 10;
        SDL_RenderSetViewport(gRenderer, &bottomViewport);

        // Render texture to screen
        SDL_RenderCopy(gRenderer, gTexture, nullptr, nullptr);

        // Update screen
        SDL_RenderPresent(gRenderer);
      }
    }
  }

  // Free resources and close SDL
  close();

  return 0;
}