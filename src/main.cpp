#include <iostream>
#include <SDL2/SDL.h>
#include "constants.h"
#include "screen.h"

Screen theScreen;
Timer timer;

int main() {

    theScreen.Init(SCREEN_WIDTH, SCREEN_HEIGHT, MAGNIFICATION);

    //pixel draw code
    //theScreen.Draw(SCREEN_WIDTH/2, SCREEN_HEIGHT/2, Yellow());

    //line draw code
    // Line2D line = {Vector2D(0,0), Vector2D(SCREEN_WIDTH/2, SCREEN_HEIGHT)};
    // theScreen.Draw(line, White());

    //rotating line draw code
    float rotationSpeed = 60.0f * M_PI / 180.0f;
    Vector2D rotatingPoint = {0,0};
    Vector2D originPoint = {SCREEN_WIDTH/2, SCREEN_HEIGHT/2};

    SDL_Event sdlEvent;
    bool running = true;
    while (running){

        timer.Start();
        
        rotatingPoint.Rotate((timer.DeltaTime() * rotationSpeed), originPoint);
        Line2D line = {rotatingPoint, originPoint};
        theScreen.Draw(line, Magenta());

        while(SDL_PollEvent(&sdlEvent)){
            switch (sdlEvent.type){
                case SDL_QUIT:
                    running = false;
                    break;
            }
        }

        theScreen.SwapBuffers();

        timer.End();
    }
    
    return 0;
}