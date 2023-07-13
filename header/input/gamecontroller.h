#ifndef INPUT_GAMECONTROLLER_H
#define INPUT_GAMECONTROLLER_H

#include "inputaction.h"

class GameController{

public:

    GameController();

    InputAction GetActionForKey(InputKey key);
    void AddInputActionForKey (const ButtonAction& buttonAction);
    void ClearAll();

    static bool IsPressed(InputState state);
    static bool IsReleased(InputState state);
    
    static InputKey ActionKey();
    static InputKey CancelKey();
    static InputKey LeftKey();
    static InputKey RightKey();
    static InputKey UpKey();
    static InputKey DownKey();

private:
    std::vector<ButtonAction> gButtonActions;

};




#endif