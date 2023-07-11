#include "app.h"

App& App::Singleton(){

    static App theApp;
    return theApp;
}

bool App::Init (uint32_t width, uint32_t height, uint32_t mag){

    anoptrWindow = aScreen.Init(width, height, mag);
    return anoptrWindow != nullptr;
}

void App::Run(){

    if (anoptrWindow)
    {
        Triangle triangle = {Vector2D (60, 10), Vector2D (10, 110), Vector2D (110,110)};
        Rectangle rectangle = {Vector2D(aScreen.Width()/2-100, aScreen.Height()/2-100),150,200};
        Circle circle = {Vector2D(aScreen.Width()/2 +50, aScreen.Height()/2 -150), 80};
        std::cout << "Shapes created...\n";

        uint32_t lastTick = SDL_GetTicks();
        uint32_t currentTick = lastTick;
        uint32_t accumulator = 0;

        SDL_Event sdlEvent;
        bool running = true;
        while (running){

            currentTick = SDL_GetTicks();
            uint32_t frameTime = currentTick - lastTick;

            if (frameTime > MAX_FRAME_RATE)
            {
                frameTime = MAX_FRAME_RATE;
            }

            lastTick = currentTick;
            accumulator += frameTime;
            
            //Input
            while(SDL_PollEvent(&sdlEvent)){
                switch (sdlEvent.type){
                    case SDL_QUIT:
                        running = false;
                        break;
                }
            }

            // Update
            while (accumulator >= DELTA_TIME)
            {
                //update current scene by dt
                std::cout << "Delta time step: " << DELTA_TIME << std::endl;
                accumulator -= DELTA_TIME;
            }

            // Render
            aScreen.Draw (triangle, Lilac(), true, Lilac());
            aScreen.Draw (rectangle, Green(), true, Green());
            aScreen.Draw (circle, Color (245, 190, 100, 100), true, Color (245, 190, 100, 100));

            aScreen.SwapBuffers();
            
        }
    }
}