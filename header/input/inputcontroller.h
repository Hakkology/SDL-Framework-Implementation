#ifndef INPUT_INPUTCONTROLLER_H
#define INPUT_INPUTCONTROLLER_H

#include "inputaction.h"
#include "gamecontroller.h"

struct GameController;

class InputController{

public:

    InputController();

    void init(InputAction quitAction);
    void Update(uint32_t dt);
    
    void SetGameController(GameController* controller);

private:
    InputAction gQuit;
    GameController* mnoptrCurrentController;

};




#endif