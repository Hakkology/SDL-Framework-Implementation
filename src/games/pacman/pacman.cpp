#include "pacman.h"
#include "app.h"
#include "constants.h"

void Pacman::Init(GameController &controller){

    pPacmanSpriteSheet.Load("PacmanSprites");
    pPacman.Init(pPacmanSpriteSheet, App::Singleton().GetBasePath() + "Assets/Pacman_animations.txt", Vector2D::Zero, PACMAN_MOVEMENT_SPEED, false);
    pLevel.Init(App::Singleton().GetBasePath()+ "Assets/Pacman_level.txt", &pPacmanSpriteSheet, &pPacman);
    
    SetupGhosts();
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

    for (size_t i = 0; i < NUM_GHOSTS; ++i)
    {
        pGhosts[i].Update(dt);
    }

    pLevel.Update(dt);

    if (pLevel.IsLevelOver())
    {
        pLevel.IncreaseLevel();
    }
}

void Pacman::Draw(Screen &screen){

    pLevel.Draw(screen);
    DrawScoreTable(screen);
    pPacman.Draw(screen);

    for(auto& ghost: pGhosts){

        ghost.Draw(screen);
    }

    DrawLives(screen);
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

void Pacman::DrawLives(Screen &screen){

    const uint32_t X_PADDING =1;

    auto sprite = pPacmanSpriteSheet.GetSprite(PACMAN_LIFE_SPRITE_NAME);
    uint32_t xPos = X_PADDING;

    for (int i = 0; i < pNumLives; ++i)
    {
        screen.Draw(pPacmanSpriteSheet, PACMAN_LIFE_SPRITE_NAME, Vector2D(xPos, App::Singleton().Height() - sprite.height));
        xPos += X_PADDING + sprite.width;
    }
}

void Pacman::ResetLevel(){

}

void Pacman::ResetGame(){

    pNumLives = MAX_NUM_LIVES;
    pPressedDirection = PACMAN_MOVEMENT_NONE;
    pPacman.ResetScore();
    pLevel.ResetToFirstLevel();
    ResetLevel();
}

void Pacman::UpdatePacmanMovement(){


    PacmanMovement currentDirection = pPacman.GetMovementDirection();

    if (pLevel.WillCollide(pPacman.GetBoundingBox(), currentDirection))
    {
        pPacman.Stop();
        return;
    }

    if (pPressedDirection != PACMAN_MOVEMENT_NONE && currentDirection != pPressedDirection)
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

void Pacman::SetupGhosts()
{

    pGhosts.resize(NUM_GHOSTS);

    PacmanGhost blinky;
    blinky.Init (pPacmanSpriteSheet, App::Singleton().GetBasePath() + "Assets/Ghost_animations.txt", 
    pLevel.GetGhostSpawnPoints()[BLINKY], PACMAN_GHOST_MOVEMENT_SPEED, true, Red());
    blinky.SetMovementDirection(PACMAN_MOVEMENT_LEFT);
    pGhosts[BLINKY] = blinky;

    PacmanGhost pinky;
    pinky.Init (pPacmanSpriteSheet, App::Singleton().GetBasePath() + "Assets/Ghost_animations.txt", 
    pLevel.GetGhostSpawnPoints()[PINKY], PACMAN_GHOST_MOVEMENT_SPEED, true, Pink());
    pinky.SetMovementDirection(PACMAN_MOVEMENT_DOWN);
    pGhosts[PINKY] = pinky;

    PacmanGhost inky;
    inky.Init (pPacmanSpriteSheet, App::Singleton().GetBasePath() + "Assets/Ghost_animations.txt", 
    pLevel.GetGhostSpawnPoints()[INKY], PACMAN_GHOST_MOVEMENT_SPEED, true, Cyan());
    inky.SetMovementDirection(PACMAN_MOVEMENT_UP);
    pGhosts[INKY] = inky;

    PacmanGhost clyde;
    clyde.Init (pPacmanSpriteSheet, App::Singleton().GetBasePath() + "Assets/Ghost_animations.txt", 
    pLevel.GetGhostSpawnPoints()[CLYDE], PACMAN_GHOST_MOVEMENT_SPEED, true, Orange());
    clyde.SetMovementDirection(PACMAN_MOVEMENT_RIGHT);
    pGhosts[CLYDE] = clyde;
}


