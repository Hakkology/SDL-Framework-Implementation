#include "screen.h"

Screen::Screen(): gWidth(0), gHeight(0), 
                    moptrWindow(nullptr), monoptrWindowSurface(nullptr){

}

SDL_Window *Screen::Init(uint32_t w, uint32_t h, uint32_t mag){
    
    if (SDL_Init(SDL_INIT_VIDEO))
    {
        std::cout << "Error SDL_Init Failed" << std::endl;
        return nullptr;
    }

    gWidth = w;
    gHeight = h;

    // window initializer
    moptrWindow = SDL_CreateWindow("Bilqe", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, gWidth*mag, gHeight*mag, 0);
    
    if (moptrWindow == nullptr)
    {
        std::cout << "Window could not be created with error: " << SDL_GetError() << std::endl;
        return nullptr;
    }

    // window surface initializer
    if (moptrWindow)
    {
        monoptrWindowSurface = SDL_GetWindowSurface(moptrWindow);

        // color and pixel format initializer
        SDL_PixelFormat *pixelFormat = monoptrWindowSurface->format;
        Color::InitColorFormat(pixelFormat);
        gClearColor = Black();
        gBackBuffer.Init(pixelFormat -> format, gWidth, gHeight);
        gBackBuffer.Clear(gClearColor);
    }
    
    return moptrWindow;

}

void Screen::SwapBuffers(){
    
    assert(moptrWindow);
    if (moptrWindow)
    {
        ClearScreen();

        SDL_BlitScaled(gBackBuffer.GetSurface(), nullptr, monoptrWindowSurface, nullptr);
        SDL_UpdateWindowSurface(moptrWindow);

        gBackBuffer.Clear(gClearColor);
    }
}

void Screen::Draw(int x, int y, const Color &color){

    assert(moptrWindow);
    if (moptrWindow) {gBackBuffer.SetPixel(color, x, y);}

}

void Screen::Draw(const Vector2D &point, const Color &color){
    
    assert(moptrWindow);
    if (moptrWindow) {gBackBuffer.SetPixel(color, point.GetX(), point.GetY());}
}

void Screen::Draw(const Line2D &line, const Color &color) {

    assert(moptrWindow);
    if (moptrWindow)
    {
        int dx, dy;

        int x0 = roundf(line.GetP0().GetX());
        int y0 = roundf(line.GetP0().GetY());
        int x1 = roundf(line.GetP1().GetX());
        int y1 = roundf(line.GetP1().GetY());

        dx = x1 - x0;
        dy = y1 - y0;

        // boolean expressions are either 1 or -1 in c++, so these expressions are just -1, 0 or 1, which defines the direction.
        signed const char ix((dx>0)-(dx<0));
        signed const char iy((dx>0)-(dx<0));

        // to avoid floating point math, shall be divided by two.
        dx = abs (dx) * 2;
        dy = abs (dy) * 2;

        Draw (x0, y0, color);
        if (dx >= dy)
        {
            int d = dy - dx/2;
            while (x0 != x1){
                if (d >=0)
                {
                    d -= dx;
                    y0 += iy;
                }
                d += dy;
                x0 += ix;

                Draw(x0, y0, color);
            }
        }
        else
        {
            int d = dx - dy/2;
            while (y0 != y1){
                if (d >= 0)
                {
                    d -= dy;
                    x0 += ix;
                }
                d += dx;
                x0 += iy;

                Draw(x0, y0, color);
            }
        }
    }

}

void Screen::ClearScreen(){
    assert(moptrWindow);
    if (moptrWindow)
    {
        SDL_FillRect(monoptrWindowSurface, nullptr, gClearColor.GetPixelColor());
    }
}

Screen::~Screen(){

    if (moptrWindow)
    {
        SDL_DestroyWindow(moptrWindow);
        moptrWindow = nullptr;
    }
    SDL_Quit();
}

