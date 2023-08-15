#include "pacman.h"
#include "app.h"
#include "constants.h"

void Pacman::Init(GameController &controller){

    pReleaseGhostTimer = 0;
    pPacmanSpriteSheet.Load("PacmanSprites");
    pPacman.Init(pPacmanSpriteSheet, App::Singleton().GetBasePath() + "Assets/Pacman_animations.txt", Vector2D::Zero, PACMAN_MOVEMENT_SPEED, false);
    pLevel.Init(App::Singleton().GetBasePath()+ "Assets/Pacman_level.txt", &pPacmanSpriteSheet);
    
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

    pReleaseGhostTimer += dt;

    for (size_t i = 0; i < NUM_GHOSTS; ++i)
    {
        PacmanGhost& ghost = pGhosts[i];
        PacmanGhostAI& ghostAI = pGhostAIs[i];

        if (pReleaseGhostTimer >= RELEASE_GHOST_TIME && ghostAI.IsInPen() && !ghost.IsReleased())
        {
            pReleaseGhostTimer = 0;
            ghost.ReleaseFromPen();
        }
        
        auto direction = ghostAI.Update(dt, pPacman, pLevel, pGhosts);

        if (ghost.IsReleased() && ghost.CanChangeDirection() || 
            (ghost.IsReleased() && ghostAI.WantsToLeavePen() && direction != PACMAN_MOVEMENT_NONE))
        {
            if (direction != ghost.GetMovementDirection())
            {
                ghost.SetMovementDirection(direction);
                ghost.LockCanChangeDirection();
            }
        }

        ghost.Update(dt);
    }

    pLevel.Update(dt, pPacman, pGhosts, pGhostAIs);

    if (pLevel.IsLevelOver())
    {
        pLevel.IncreaseLevel();
        ResetLevel();
    }
}

void Pacman::Draw(Screen &screen){

    pLevel.Draw(screen);
    DrawScoreTable(screen);
    pPacman.Draw(screen);

    for(auto& ghost: pGhosts){

        ghost.Draw(screen);
    }

    for(auto& ghostAI: pGhostAIs){

        ghostAI.Draw(screen);
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

    pPacman.MoveTo(pLevel.GetPacmanSpawnLocation());
    pPacman.ResetToFirstAnimation();

    for(auto& ghost: pGhosts){

        ghost.ResetToFirstPosition();
    }

    pGhosts[BLINKY].ReleaseFromPen();
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
    const Vector2D BLINKY_SCATTER_POS = Vector2D(App::Singleton().Width() - 24, 0);
    const Vector2D INKY_SCATTER_POS = Vector2D(App::Singleton().Width(), App::Singleton().Height());
    const Vector2D PINKY_SCATTER_POS = Vector2D(24,0);
    const Vector2D CLYDE_SCATTER_POS = Vector2D(0, App::Singleton().Height());

    pGhosts.resize(NUM_GHOSTS);
    pGhostAIs.resize(NUM_GHOSTS);

    PacmanGhost blinky;
    blinky.Init (pPacmanSpriteSheet, App::Singleton().GetBasePath() + "Assets/Ghost_animations.txt", 
    pLevel.GetGhostSpawnPoints()[BLINKY], PACMAN_GHOST_MOVEMENT_SPEED, true, Red());
    blinky.SetMovementDirection(PACMAN_MOVEMENT_LEFT);
    pGhosts[BLINKY] = blinky;

    auto blinkyAI = PacmanGhostAI();
    blinkyAI.Init(pGhosts[BLINKY], blinky.GetBoundingBox().GetWidth(), BLINKY_SCATTER_POS, pLevel.GetGhostSpawnPoints()[PINKY], pLevel.GetGhostSpawnPoints()[BLINKY], BLINKY);
    pGhostAIs[BLINKY] = blinkyAI;

    PacmanGhost pinky;
    pinky.Init (pPacmanSpriteSheet, App::Singleton().GetBasePath() + "Assets/Ghost_animations.txt", 
    pLevel.GetGhostSpawnPoints()[PINKY], PACMAN_GHOST_MOVEMENT_SPEED, true, Pink());
    pinky.SetMovementDirection(PACMAN_MOVEMENT_DOWN);
    pGhosts[PINKY] = pinky;

    auto pinkyAI = PacmanGhostAI();
    pinkyAI.Init(pGhosts[PINKY], pinky.GetBoundingBox().GetWidth(), PINKY_SCATTER_POS, pLevel.GetGhostSpawnPoints()[PINKY], pLevel.GetGhostSpawnPoints()[BLINKY], PINKY);
    pGhostAIs[PINKY] = pinkyAI;

    PacmanGhost inky;
    inky.Init (pPacmanSpriteSheet, App::Singleton().GetBasePath() + "Assets/Ghost_animations.txt", 
    pLevel.GetGhostSpawnPoints()[INKY], PACMAN_GHOST_MOVEMENT_SPEED, true, Cyan());
    inky.SetMovementDirection(PACMAN_MOVEMENT_UP);
    pGhosts[INKY] = inky;

    auto inkyAI = PacmanGhostAI();
    inkyAI.Init(pGhosts[INKY], inky.GetBoundingBox().GetWidth(), INKY_SCATTER_POS, pLevel.GetGhostSpawnPoints()[PINKY], pLevel.GetGhostSpawnPoints()[BLINKY], INKY);
    pGhostAIs[INKY] = inkyAI;

    PacmanGhost clyde;
    clyde.Init (pPacmanSpriteSheet, App::Singleton().GetBasePath() + "Assets/Ghost_animations.txt", 
    pLevel.GetGhostSpawnPoints()[CLYDE], PACMAN_GHOST_MOVEMENT_SPEED, true, Orange());
    clyde.SetMovementDirection(PACMAN_MOVEMENT_RIGHT);
    pGhosts[CLYDE] = clyde;

    auto clydeAI = PacmanGhostAI();
    clydeAI.Init(pGhosts[CLYDE], inky.GetBoundingBox().GetWidth(), CLYDE_SCATTER_POS, pLevel.GetGhostSpawnPoints()[PINKY], pLevel.GetGhostSpawnPoints()[BLINKY], CLYDE);
    pGhostAIs[CLYDE] = clydeAI;

    for (size_t i = 0; i < NUM_GHOSTS; ++i)
    {
        pGhosts[i].SetGhostDelegate(pGhostAIs[i]);
    }
}


