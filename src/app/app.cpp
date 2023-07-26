#include "app.h"

App& App::Singleton(){

    static App theApp;
    return theApp;
}

bool App::Init (uint32_t width, uint32_t height, uint32_t mag){

    anoptrWindow = aScreen.Init(width, height, mag);
    std::unique_ptr<ArcadeScene> arcadeScene = std::make_unique<ArcadeScene>();
    PushScene(std::move(arcadeScene));

    //Temporary
    {
        std::unique_ptr<BreakOut> breakoutGame = std::make_unique<BreakOut>();
        
        std::unique_ptr<GameScene> breakoutScene = std::make_unique<GameScene>(std::move(breakoutGame));

        PushScene (std::move(breakoutScene));
    }

    return anoptrWindow != nullptr;
}

void App::Run(){

    if (anoptrWindow)
    {
        bool running = true;

        uint32_t lastTick = SDL_GetTicks();
        uint32_t currentTick = lastTick;
        uint32_t accumulator = 0;

        aInputController.init([&running](uint32_t DELTA_TIME, InputState state){
            running = false;
        });

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
            aInputController.Update(DELTA_TIME);

            Scene* topScene = App::TopScene();
            assert(topScene && "What is a scene?");

            if (topScene)
            {
                // Update
                while (accumulator >= DELTA_TIME)
                {
                    //update current scene by dt
                    topScene->Update(DELTA_TIME);
                    accumulator -= DELTA_TIME;
                }

                topScene->Draw(aScreen);
            }
            
            aScreen.SwapBuffers();
            
        }
    }
}

void App::PushScene(std::unique_ptr<Scene> scene){

    assert(scene && "No scene found through Pointer.");
    if (scene)
    {
        scene->Init();
        aInputController.SetGameController(scene->GetGameController());
        aSceneStack.emplace_back(std::move(scene));
        SDL_SetWindowTitle(anoptrWindow, TopScene() -> GetSceneName().c_str());
    }
    
}

void App::PopScene(){

    if (aSceneStack.size() > 1)
    {
        aSceneStack. pop_back();
    }

    if (TopScene())
    {
        aInputController.SetGameController(TopScene()->GetGameController());
        SDL_SetWindowTitle(anoptrWindow, TopScene() -> GetSceneName().c_str());
    }
}

Scene *App::TopScene(){

    if (aSceneStack.empty())
    {
        return nullptr;
    }
    
    return aSceneStack.back().get();
}

const std::string &App::GetBasePath(){

    static std::string basePath = SDL_GetBasePath();
    return basePath;
}
