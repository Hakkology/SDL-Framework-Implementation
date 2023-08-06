#include "pacman.h"
#include "app.h"

void Pacman::Init(GameController &controller){

    pPacmanSpriteSheet.Load("PacmanSprites");

    pLevel.Init(App::Singleton().GetBasePath()+ "Assets/Pacman_level.txt");

    pPacman.Init(pPacmanSpriteSheet, App::Singleton().GetBasePath() + "Assets/Pacman_animations.txt", 
    Vector2D::Zero, PACMAN_MOVEMENT_SPEED, false);

    ResetGame();

    ButtonAction leftAction;
    leftAction.key = GameController::LeftKey();
    leftAction.action = [this] (uint32_t dt, InputState state){
        
        HandleGameControllerState(dt, state, PACMAN_MOVEMENT_LEFT);
    };
    controller.AddInputActionForKey(leftAction);

    ButtonAction rightAction;
    rightAction.key = GameController::RightKey();
    rightAction.action = [this] (uint32_t dt, InputState state){
        
        HandleGameControllerState(dt, state, PACMAN_MOVEMENT_RIGHT);
    };
    controller.AddInputActionForKey(rightAction);

    ButtonAction upAction;
    upAction.key = GameController::UpKey();
    upAction.action = [this] (uint32_t dt, InputState state){
        
        HandleGameControllerState(dt, state, PACMAN_MOVEMENT_UP);
    };
    controller.AddInputActionForKey(upAction);

    ButtonAction downAction;
    downAction.key = GameController::DownKey();
    downAction.action = [this] (uint32_t dt, InputState state){
        
        HandleGameControllerState(dt, state, PACMAN_MOVEMENT_DOWN);
    };
    controller.AddInputActionForKey(downAction);
}

void Pacman::Update(uint32_t dt){

    pLevel.Update(dt);
    UpdatePacmanMovement();
    pPacman.Update(dt);
}

void Pacman::Draw(Screen &screen){

    pLevel.Draw(screen);
    pPacman.Draw(screen);
}

const std::string &Pacman::GetName() const{

    static std::string name = "Pacmania!";
    return name;
}

void Pacman::ResetGame(){

    pPressedDirection = PACMAN_MOVEMENT_NONE;
    pPacman.ResetScore();
}

void Pacman::UpdatePacmanMovement(){

    if (pPressedDirection != PACMAN_MOVEMENT_NONE)
    {
        pPacman.SetMovementDirection(pPressedDirection);
    }
}

void Pacman::HandleGameControllerState(uint32_t dt, InputState state, PacmanMovement direction){

    if (GameController::IsPressed(state))
    {
        pPressedDirection = direction;
    }
    else if (GameController::IsReleased(state) && pPressedDirection == direction)
    {
        pPressedDirection = PACMAN_MOVEMENT_NONE;
    }
    
}
