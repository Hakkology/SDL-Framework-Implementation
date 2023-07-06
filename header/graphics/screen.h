#ifndef GRAPHICS_SCREEN_H
#define GRAPHICS_SCREEN_H

#include <stdint.h>
#include <cassert>
#include <cmath>

#include <SDL2/SDL.h>

#include "screenbuffer.h"
#include "color.h"
#include "vector2D.h"
#include "line2D.h"

class Vector2D;
struct SDL_window;
struct SDL_Surface;

class Screen{

public:

    Screen();
    ~Screen();

    SDL_Window* Init(uint32_t w, uint32_t h, uint32_t mag);
    void SwapBuffers();
    
    inline void SetClearColor(const Color& clearColor) {gClearColor = clearColor;}
    inline uint32_t Width() const {return gWidth;}
    inline uint32_t Height() const {return gHeight;}

    // Draw methods

    void Draw (int x, int y, const Color& color);
    void Draw (const Vector2D& point, const Color& color);
    void Draw (const Line2D& line, const Color& color);

private:

    Screen& operator= (const Screen& screen);
    
    void ClearScreen();

    uint32_t gWidth;
    uint32_t gHeight;
    
    Color gClearColor;
    ScreenBuffer gBackBuffer;

    SDL_Window* moptrWindow;
    SDL_Surface* monoptrWindowSurface;

};

#endif