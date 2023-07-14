#include "gamecontroller.h"

#include <SDL2/SDL.h>


GameController::GameController(){

    
}

InputAction GameController::GetActionForKey(InputKey key){

    for (const auto& buttonAction: gButtonActions)
    {
        if (key == buttonAction.key)
        {
            return buttonAction.action;
        }
        
    }

    return [] (uint32_t, InputState) {};
}

void GameController::AddInputActionForKey (const ButtonAction& buttonAction){

    gButtonActions.push_back(buttonAction);
}

void GameController::ClearAll(){

    gButtonActions.clear();
}

bool GameController::IsPressed(InputState state){

    return state == SDL_PRESSED;
}

bool GameController::IsReleased(InputState state){

    return state == SDL_RELEASED;
}

InputKey GameController::ActionKey(){

    return static_cast<InputKey>(SDLK_e);
}

InputKey GameController::CancelKey(){

    return static_cast<InputKey>(SDLK_q);
}

InputKey GameController::LeftKey(){

    return static_cast<InputKey>(SDLK_a);
}

InputKey GameController::RightKey(){

    return static_cast<InputKey>(SDLK_r);
}

InputKey GameController::UpKey(){

    return static_cast<InputKey>(SDLK_w);
}

InputKey GameController::DownKey(){

    return static_cast<InputKey>(SDLK_s);
}