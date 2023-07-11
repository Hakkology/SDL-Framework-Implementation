#include "app.h"
#include "arcadeScene.h"

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

        uint32_t lastTick = SDL_GetTicks();
        uint32_t currentTick = lastTick;
        uint32_t accumulator = 0;

        std::unique_ptr<ArcadeScene> arcadeScene = std::make_unique<ArcadeScene>();
        arcadeScene -> Init();

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
                arcadeScene->Update(DELTA_TIME);
                std::cout << "Delta time step: " << DELTA_TIME << std::endl;
                accumulator -= DELTA_TIME;
            }

            arcadeScene->Draw(aScreen);
            aScreen.SwapBuffers();
            
        }
    }
}