//
// Created by liuso on 2022/1/1.
//

#pragma once

#include <SDL.h>
#include <string>

class LTexture {
 public:
  // Initializes variables
  LTexture();

  // Deallocates memory
  ~LTexture();

  // Loads image at specified path
  bool loadFromFile(SDL_Renderer *renderer, std::string filepath);

  // Deallocates texture
  void free();

  void setColor(Uint8 red, Uint8 green, Uint8 blue);

  void setBlendMode(SDL_BlendMode blending);

  void setAlpha(Uint8 alpha);

  // Renders texture at given point
  void render(SDL_Renderer *renderer, int x, int y, SDL_Rect *clip = nullptr);

  // Gets image dimensions
  int getWidth() const { return mWidth; };
  int getHeight() const { return mHeight; };

 private:
  // The actual hardware texture
  SDL_Texture *mTexture;

  // Image dimensions
  int mWidth;
  int mHeight;
};

