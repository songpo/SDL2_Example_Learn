//
// Created by liuso on 2022/1/1.
//

#include <SDL_image.h>
#include "texture_mananger.h"

LTexture::LTexture() {
  // Initialize
  mTexture = nullptr;
  mWidth = 0;
  mHeight = 0;
}

LTexture::~LTexture() {
  // Deallocate
  free();
}

bool LTexture::loadFromFile(SDL_Renderer *renderer, std::string filepath) {
  // Get rid of preexisting texture
  free();

  // The final texture
  SDL_Texture *newTexture = nullptr;

  // Load image at specified path
  SDL_Surface *loadedSurface = IMG_Load(filepath.c_str());
  if (loadedSurface == nullptr) {
    SDL_Log("Unable to load image %s! SDL_image Error:%s", filepath.c_str(), IMG_GetError());
  } else {
    // Color key image
    SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));

    // Create texture from surface pixels
    newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
    if (newTexture == nullptr) {
      SDL_Log("Unable to create texture %s! SDL_image Error:%s", filepath.c_str(), IMG_GetError());
    } else {
      // Get image dimensions
      mWidth = loadedSurface->w;
      mHeight = loadedSurface->h;
    }

    // Get rid of old loaded surface
    SDL_FreeSurface(loadedSurface);
  }

  mTexture = newTexture;

  return newTexture != nullptr;
}

void LTexture::free() {
  // Free texture if it exists
  if (mTexture != nullptr) {
    SDL_DestroyTexture(mTexture);
    mTexture = nullptr;
    mWidth = 0;
    mHeight = 0;
  }
}

void LTexture::render(SDL_Renderer *renderer, int x, int y, SDL_Rect *clip) {
  // Set rendering space and render to screen
  SDL_Rect renderQuad = {x, y, mWidth, mHeight};
  if (clip != nullptr) {
    renderQuad.w = clip->w;
    renderQuad.h = clip->h;
  }

  // Render to scene
  SDL_RenderCopy(renderer, mTexture, clip, &renderQuad);
}
