#include <iostream>
#include <SDL2/SDL.h>

#include "constants.h"
#include "screen.h"


Timer timer;

int main() {

    std::cout << "Starting program...\n";

    Screen theScreen;
    theScreen.Init(SCREEN_WIDTH, SCREEN_HEIGHT, MAGNIFICATION);

    std::cout << "Screen initialized...\n";

    Triangle triangle = {Vector2D (60, 10), Vector2D (10, 110), Vector2D (110,110)};
    std::cout << "Triangle created...\n";

    theScreen.Draw (triangle, Red());
    std::cout << "Triangle drawn...\n";

    theScreen.SwapBuffers();
    std::cout << "Buffers swapped...\n";

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