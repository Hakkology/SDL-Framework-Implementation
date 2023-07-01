#include <iostream>

#include <SDL2/SDL.h>

#include "constants.h"
#include "color.h"
#include "screenbuffer.h"

int main() {

    if (SDL_Init(SDL_INIT_VIDEO))
    {
        std::cout << "Error SDL_Init Failed" << std::endl;
        return 1;
    }

    // window initializer
    SDL_Window* optrWindow = SDL_CreateWindow("Bilqe", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
                                                        SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    
    if (optrWindow == nullptr)
    {
        std::cout << "Window could not be created with error: " << SDL_GetError() << std::endl;
        return 1;
    }

    // window surface initializer
    SDL_Surface* noptrWindowSurface = SDL_GetWindowSurface(optrWindow);

    // color and pixel format initializer
    SDL_PixelFormat *pixelFormat =noptrWindowSurface->format;
    Color::InitColorFormat(pixelFormat);

    // screenbuffer initializer
    ScreenBuffer screenBuffer;
    screenBuffer.Init(pixelFormat->format, noptrWindowSurface->w, noptrWindowSurface->h);
    screenBuffer.SetPixel(Red(), SCREEN_WIDTH/2, SCREEN_HEIGHT/2);
    SDL_BlitSurface(screenBuffer.GetSurface(), nullptr, noptrWindowSurface, nullptr);

    SDL_UpdateWindowSurface(optrWindow);

    SDL_Event sdlEvent;
    bool running = true;
    
    while (running){
        while(SDL_PollEvent(&sdlEvent)){
            switch (sdlEvent.type){
                case SDL_QUIT:
                    running = false;
                    break;
            }
        }
    }

    SDL_DestroyWindow(optrWindow);
    SDL_Quit();
    
    return 0;
}