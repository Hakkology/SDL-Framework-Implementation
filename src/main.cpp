#include <iostream>

#include <SDL2/SDL.h>

#include "constants.h"

void SetPixel(SDL_Surface * noptrWindowSurface, uint32_t color, int x, int y);
size_t GetIndex(SDL_Surface * noptrSurface, int r, int c);

int main() {

    if (SDL_Init(SDL_INIT_VIDEO))
    {
        std::cout << "Error SDL_Init Failed" << std::endl;
        return 1;
    }

    SDL_Window* optrWindow = SDL_CreateWindow("Bilqe", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
                                                        SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    
    if (optrWindow == nullptr)
    {
        std::cout << "Window could not be created with error: " << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_Surface* noptrWindowSurface = SDL_GetWindowSurface(optrWindow);

    uint32_t color = 0XFF0000;

    SetPixel(noptrWindowSurface, color, SCREEN_WIDTH/2, SCREEN_HEIGHT/2);

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

void SetPixel(SDL_Surface * noptrWindowSurface, uint32_t color, int x, int y){

    SDL_LockSurface(noptrWindowSurface);

    uint32_t * pixels = (uint32_t*) noptrWindowSurface->pixels;
    size_t index = GetIndex(noptrWindowSurface, y, x);
    pixels[index] = color;

    SDL_UnlockSurface(noptrWindowSurface);

}

size_t GetIndex(SDL_Surface * noptrSurface, int r, int c){

    return r * noptrSurface->w +c;
}