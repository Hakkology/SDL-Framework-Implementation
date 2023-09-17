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
    static InputKey PushKey();
    static InputKey ModifyKey();

    inline const MouseMovedAction GetMouseMoveAction() {return gMouseMovedAction;}
    inline void SetMouseMovedAction(const MouseMovedAction& mouseMovedAction) {gMouseMovedAction=mouseMovedAction;}

    MouseInputAction GetMouseButtonActionForMouseButton(MouseButton button);
    void AddMouseButtonAction(const MouseButtonAction& MouseMovedAction);

    static MouseButton LeftMouseButton();
    static MouseButton RightMouseButton();

private:

    std::vector<ButtonAction> gButtonActions;
    std::vector<MouseButtonAction> gMouseButtonActions;
    MouseMovedAction gMouseMovedAction;
};




#endif