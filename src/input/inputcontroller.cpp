#include "inputcontroller.h"

InputController::InputController():gQuit(nullptr), mnoptrCurrentController(nullptr){


}

void InputController::init(InputAction quitAction){

    gQuit = quitAction;
}

void InputController::Update(uint32_t dt){

    SDL_Event sdlEvent;

    while (SDL_PollEvent(&sdlEvent))
    {
        switch (sdlEvent.type)
        {
        case SDL_QUIT:
            gQuit(dt, SDL_PRESSED);
            break;
        case SDL_KEYDOWN:
        case SDL_KEYUP:
            if (mnoptrCurrentController)
            {
                InputAction action = mnoptrCurrentController->GetActionForKey(sdlEvent.key.keysym.sym);

                action(dt, static_cast<InputState>(sdlEvent.key.state));
            }
            break;
        default:
            break;
        }
    }
    


}

void InputController::SetGameController(GameController* controller){

    mnoptrCurrentController = controller;
}
