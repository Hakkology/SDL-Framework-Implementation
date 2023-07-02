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

