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

bool IsPressed(InputState state){

    return state == SDL_PRESSED;
}

bool IsReleased(InputState state){

    return state == SDL_RELEASED;
}

InputKey ActionKey(){

    return static_cast<InputKey>(SDLK_e);
}

static InputKey CancelKey(){

    return static_cast<InputKey>(SDLK_q);
}

static InputKey LeftKey(){

    return static_cast<InputKey>(SDLK_a);
}

static InputKey RightKey(){

    return static_cast<InputKey>(SDLK_r);
}

static InputKey UpKey(){

    return static_cast<InputKey>(SDLK_w);
}

static InputKey DownKey(){

    return static_cast<InputKey>(SDLK_s);
}