#include <iostream>

#include <SDL2/SDL.h>

#include "constants.h"
#include "color.h"
#include "screen.h"

int main() {

    Screen theScreen;
    theScreen.Init(SCREEN_WIDTH, SCREEN_HEIGHT, MAGNIFICATION);
    theScreen.Draw(SCREEN_WIDTH/2, SCREEN_HEIGHT/2, Yellow());
    theScreen.SwapBuffers();

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
    
    return 0;
}