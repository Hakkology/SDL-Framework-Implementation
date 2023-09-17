#include "gamecontroller.h"

#include <SDL2/SDL.h>


GameController::GameController(): gMouseMovedAction(nullptr){

    
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

InputKey GameController::PushKey(){

    return static_cast<InputKey>(SDLK_f);
}

InputKey GameController::ModifyKey(){

    return static_cast<InputKey>(SDLK_r);
}

InputKey GameController::LeftKey(){

    return static_cast<InputKey>(SDLK_a);
}

InputKey GameController::RightKey(){

    return static_cast<InputKey>(SDLK_d);
}

InputKey GameController::UpKey(){

    return static_cast<InputKey>(SDLK_w);
}

InputKey GameController::DownKey(){

    return static_cast<InputKey>(SDLK_s);
}

MouseInputAction GameController::GetMouseButtonActionForMouseButton(MouseButton button){

    for (const auto& ButtonAction: gMouseButtonActions)
    {
        if (button == ButtonAction.mouseButton)
        {
            return ButtonAction.mouseInputAction;
        }
    }
    
    return [](InputState state, const MousePosition& pos){};
}

void GameController::AddMouseButtonAction(const MouseButtonAction &mouseButtonAction){

    gMouseButtonActions.push_back(mouseButtonAction);
}

MouseButton GameController::LeftMouseButton(){

    return static_cast<MouseButton>(SDL_BUTTON_LEFT);
}

MouseButton GameController::RightMouseButton(){

    return static_cast<MouseButton>(SDL_BUTTON_RIGHT);
}
