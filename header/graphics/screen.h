#ifndef GRAPHICS_SCREEN_H
#define GRAPHICS_SCREEN_H

#include <stdint.h>
#include <cassert>
#include <vector>
#include <cmath>
#include <algorithm>
#include <functional>

#include <SDL2/SDL.h>

#include "screenbuffer.h"
#include "color.h"
#include "vector2D.h"
#include "line2D.h"
#include "triangle.h"
#include "rectangle.h"
#include "circle.h"
#include "bmpimage.h"
#include "spritesheet.h"

class Vector2D;
class Line2D;
class Triangle;
class BMPImage;
class SpriteSheet;
class BmpFont;
struct SDL_Renderer;
struct SDL_PixelFormat;
struct SDL_Texture;
struct SDL_window;
struct SDL_Surface;
struct Sprite;

class Screen{

public:

    Screen();
    ~Screen();

    SDL_Window* Init(uint32_t w, uint32_t h, uint32_t mag, bool fast = true);
    void SwapBuffers();
    
    inline void SetClearColor(const Color& clearColor) {gClearColor = clearColor;}
    inline uint32_t Width() const {return gWidth;}
    inline uint32_t Height() const {return gHeight;}

    // Draw methods

    void Draw (int x, int y, const Color& color);
    void Draw (const Vector2D& point, const Color& color);
    void Draw (const Line2D& line, const Color& color);
    void Draw (const Triangle& triangle, const Color& color, bool fill=false, const Color& fillColor = White());
    void Draw (const Rectangle& rectangle, const Color& color, bool fill=false, const Color& fillColor = White());
    void Draw (const Circle& circle, const Color& color, bool fill=false, const Color& fillColor = White());

    void Draw (const BMPImage& image, const Sprite& sprite, const Vector2D& pos, const Color& overlayColor = White(), float rotation = 0.0f);
    void Draw (const SpriteSheet& ss, const std::string& spriteName, const Vector2D& pos, const Color& overlayColor = White(), float rotation = 0.0f);
    void Draw (const BmpFont& font, const std::string& textLine, const Vector2D& pos, const Color& overlayColor = White());

private:

    Screen& operator= (const Screen& screen);
    
    void ClearScreen();

    using FillPolyFunc = std::function<Color (uint32_t x, uint32_t y)>;

    void FillPoly(const std:: vector<Vector2D>& points, FillPolyFunc func);

    bool bFast;

    uint32_t gWidth;
    uint32_t gHeight;
    
    Color gClearColor;
    ScreenBuffer gBackBuffer;

    SDL_Window* moptrWindow;
    SDL_Surface* monoptrWindowSurface;
    SDL_Renderer* bRenderer;
    SDL_PixelFormat* bPixelFormat;
    SDL_Texture* bTexture;
};

#endif