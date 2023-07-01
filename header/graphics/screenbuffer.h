#ifndef GRAPHICS_SCREENBUFFER_H
#define GRAPHICS_SCREENBUFFER_H

#include <stdint.h>
#include <cassert>

#include <SDL2/SDL.h>

#include "color.h"
#include "constants.h"

class Color;
struct SDL_Surface;

class ScreenBuffer{

  

public:
    ScreenBuffer();
    ScreenBuffer(const ScreenBuffer& screenBuffer);
    ~ScreenBuffer();

    ScreenBuffer& operator=(const ScreenBuffer& screenBuffer);

    void Init(uint32_t format, uint32_t width, uint32_t height);

    inline SDL_Surface * GetSurface() {return gSurface;}

    void Clear (const Color& c = Black());

    void SetPixel (const Color& color, int x, int y);

private:

    SDL_Surface * gSurface;
    uint32_t GetIndex(int r, int c);

};

#endif