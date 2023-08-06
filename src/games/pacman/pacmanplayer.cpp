#include "pacmanplayer.h"
#include "utilities.h"

void PacmanPlayer::Init(const SpriteSheet &spriteSheet, const std::string &animationPath, 
                        const Vector2D &initialPos, uint32_t movementSpeed, bool updateSpriteOnMovement, const Color& spriteColor){

    PacmanActor::Init(spriteSheet, animationPath, initialPos, movementSpeed, false, spriteColor);

    ResetToFirstAnimation();
    ResetScore();

    pIsDying = false;
    ResetGhostEatenMultiplier();
}

void PacmanPlayer::Update(uint32_t dt){

    if (pIsDying)
    {
        pSprite.Update(dt);
        pIsDying = !isFinishedAnimation();
        return;
    }

    PacmanActor::Update(dt);
}

void PacmanPlayer::SetMovementDirection(PacmanMovement movementDir){

    PacmanMovement currentDirection = GetMovementDirection();

    if (movementDir == PACMAN_MOVEMENT_LEFT && currentDirection != PACMAN_MOVEMENT_LEFT)
    {
        SetAnimation("move_left", true);
        ResetDelta();
    }
    else if (movementDir == PACMAN_MOVEMENT_RIGHT && currentDirection != PACMAN_MOVEMENT_RIGHT)
    {
        SetAnimation("move_right", true);
        ResetDelta();
    }
    else if (movementDir == PACMAN_MOVEMENT_DOWN && currentDirection != PACMAN_MOVEMENT_DOWN)
    {
        SetAnimation("move_down", true);
        ResetDelta();
    }
    else if (movementDir == PACMAN_MOVEMENT_UP && currentDirection != PACMAN_MOVEMENT_UP)
    {
        SetAnimation("move_up", true);
        ResetDelta();
    }

    PacmanActor::SetMovementDirection(movementDir);
}

void PacmanPlayer::ResetToFirstAnimation(){

    SetAnimation("move_left", true);
    Stop();
}

void PacmanPlayer::EatenByGhost(){

    SetAnimation("death", false);
    pIsDying = true;
    ResetGhostEatenMultiplier();
}

void PacmanPlayer::ResetScore(){

    pScore = 0;
}

void PacmanPlayer::AteItem(uint32_t value){

    AddToScore(value);
}

void PacmanPlayer::AteGhost(uint32_t value){

    AddToScore(value * pGhostMultiplier);
    pGhostMultiplier *= 2;
}

void PacmanPlayer::AddToScore(uint32_t value)
{
    pScore += value;
}
