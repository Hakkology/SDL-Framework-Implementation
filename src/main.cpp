#include <iostream>
#include <SDL2/SDL.h>

#include "constants.h"
#include "screen.h"

Screen theScreen;
Timer timer;

int main() {

    theScreen.Init(SCREEN_WIDTH, SCREEN_HEIGHT, MAGNIFICATION);

    Triangle triangle = {Vector2D (60, 10), Vector2D (10, 110), Vector2D (110,110)};
    Rectangle rectangle = {Vector2D(SCREEN_WIDTH/2-125, SCREEN_HEIGHT/2-125),250,250};
    Circle circle = {Vector2D(SCREEN_WIDTH/2 +80, SCREEN_HEIGHT/2 -140), 100};
    std::cout << "Shapes created...\n";

    theScreen.Draw (triangle, Lilac());
    theScreen.Draw (rectangle, Green());
    theScreen.Draw (circle, Orange());
    std::cout << "Shapes drawn...\n";

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