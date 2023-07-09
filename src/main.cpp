#include <iostream>
#include <SDL2/SDL.h>

#include "constants.h"
#include "screen.h"

Screen theScreen;
Timer timer;

int main() {

    theScreen.Init(SCREEN_WIDTH, SCREEN_HEIGHT, MAGNIFICATION);

    Triangle triangle = {Vector2D (60, 10), Vector2D (10, 110), Vector2D (110,110)};
    std::cout << "Triangle created...\n";

    theScreen.Draw (triangle, Red());
    std::cout << "Triangle drawn...\n";

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