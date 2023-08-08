#include "pacman.h"
#include "app.h"
#include "constants.h"

void Pacman::Init(GameController &controller){

    pPacmanSpriteSheet.Load("PacmanSprites");
    pPacman.Init(pPacmanSpriteSheet, App::Singleton().GetBasePath() + "Assets/Pacman_animations.txt", Vector2D::Zero, PACMAN_MOVEMENT_SPEED, false);
    pLevel.Init(App::Singleton().GetBasePath()+ "Assets/Pacman_level.txt", &pPacman);

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
    
    UpdatePacmanMovement();
    pPacman.Update(dt);
    pLevel.Update(dt);

    if (pLevel.IsLevelOver())
    {
        pLevel.IncreaseLevel();
    }
}

void Pacman::Draw(Screen &screen){

    pLevel.Draw(screen);
    pPacman.Draw(screen);
    DrawScoreTable(screen);
}

const std::string &Pacman::GetName() const{

    static std::string name = "Pacmania!";
    return name;
}

void Pacman::DrawScoreTable(Screen &screen){

    Vector2D levelOffset = pLevel.GetLayoutOffset();
    Rectangle highScoreRect = Rectangle (Vector2D(0,4), App::Singleton().Width(), levelOffset.GetY());
    const auto& font = App::Singleton().GetFont();

    Vector2D textDrawPosition;
    std::string scoreString = std::to_string(pPacman.Score());
    textDrawPosition = font.GetDrawPosition(SCORE_STR + scoreString, highScoreRect, BFXA_CENTER, BFYA_CENTER);

    screen.Draw(font, SCORE_STR + scoreString, textDrawPosition);
}

void Pacman::ResetLevel(){

}

void Pacman::ResetGame(){

    pPressedDirection = PACMAN_MOVEMENT_NONE;
    pPacman.ResetScore();
    pLevel.ResetToFirstLevel();
}

void Pacman::UpdatePacmanMovement(){

    if (pPressedDirection != PACMAN_MOVEMENT_NONE)
    {
        if (!pLevel.WillCollide(pPacman.GetBoundingBox(), pPressedDirection))
        {
            pPacman.SetMovementDirection(pPressedDirection);
        }
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


