#include <iostream>
#include <SDL2/SDL.h>

#include "constants.h"
#include "screen.h"

Screen theScreen;
Timer timer;

int main() {

    theScreen.Init(SCREEN_WIDTH, SCREEN_HEIGHT, MAGNIFICATION);

    Triangle triangle = {Vector2D (60, 10), Vector2D (10, 110), Vector2D (110,110)};
    Rectangle rectangle = {Vector2D(SCREEN_WIDTH/2-100, SCREEN_HEIGHT/2-100),150,200};
    Circle circle = {Vector2D(SCREEN_WIDTH/2 +50, SCREEN_HEIGHT/2 -150), 80};
    std::cout << "Shapes created...\n";

    theScreen.Draw (triangle, Lilac(), true, Lilac());
    theScreen.Draw (rectangle, Green(), true, Green());
    theScreen.Draw (circle, Color (245, 190, 100, 100), true, Color (245, 190, 100, 100));
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