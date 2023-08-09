#include "pacmanghost.h"

namespace{
    const uint32_t NUM_POINTS_FOR_GHOST = 200;
}

PacmanGhost::PacmanGhost():pPoints(0), pInitialPos(Vector2D::Zero){

}

void PacmanGhost::Init(const SpriteSheet &spriteSheet, const std::string &animationsPath, const Vector2D &initialPos, uint32_t movementSpeed, bool updateSpriteOnMovement, const Color &spriteColor){

    PacmanActor::Init(spriteSheet, animationsPath, initialPos, movementSpeed, updateSpriteOnMovement, spriteColor);
    pInitialPos = initialPos;
    pPoints = NUM_POINTS_FOR_GHOST;
    ResetToFirstPosition();
}

void PacmanGhost::Update(uint32_t dt){

    Vector2D position = Position();

    PacmanActor::Update(dt);
    pCanChangeDirection = position != Position();

    if (IsVulnerable())
    {
        pVulnerabiltyTimer += dt;

        if (pState == GHOST_STATE_VULNERABLE && pVulnerabiltyTimer >= VULNERABILITY_TIME)
        {
            SetGhostState(GHOST_STATE_VULNERABLE_ENDING);
        }

        if (pState == GHOST_STATE_VULNERABLE_ENDING && pVulnerabiltyTimer >= VULNERABILITY_ENDING_TIME)
        {
            SetGhostState(GHOST_STATE_ALIVE);
        }
    }
}

void PacmanGhost::SetMovementDirection(PacmanMovement dir){

    PacmanActor::SetMovementDirection(dir);

    PacmanMovement movementDir = GetMovementDirection();

    if (pState == GHOST_STATE_ALIVE)
    {
        if (movementDir == PACMAN_MOVEMENT_RIGHT)
        {
            SetAnimation("ghost_movement_right", true);
        }
        else if (movementDir == PACMAN_MOVEMENT_UP)
        {
            SetAnimation("ghost_movement_up", true);
        }
        else if (movementDir == PACMAN_MOVEMENT_DOWN)
        {
            SetAnimation("ghost_movement_down", true);
        }
        else if (movementDir == PACMAN_MOVEMENT_LEFT)
        {
            SetAnimation("ghost_movement_left", true);
        }
    }
    else if (pState == GHOST_STATE_DEAD)
    {
        if (movementDir == PACMAN_MOVEMENT_RIGHT)
        {
            SetAnimation("ghost_dead_right", true);
        }
        else if (movementDir == PACMAN_MOVEMENT_UP)
        {
            SetAnimation("ghost_dead_up", true);
        }
        else if (movementDir == PACMAN_MOVEMENT_DOWN)
        {
            SetAnimation("ghost_dead_down", true);
        }
        else if (movementDir == PACMAN_MOVEMENT_LEFT)
        {
            SetAnimation("ghost_dead_left", true);
        }
    }
}

void PacmanGhost::Stop(){

    SetMovementDirection (PACMAN_MOVEMENT_NONE);
}

void PacmanGhost::EatenByPacman(){

    SetGhostState(GHOST_STATE_DEAD);
}

void PacmanGhost::ResetToFirstPosition(){

    pSprite.SetPosition(pInitialPos);
    SetMovementDirection(PACMAN_MOVEMENT_NONE);
    pVulnerabiltyTimer = 0;
    SetGhostState(GHOST_STATE_ALIVE);
    pCanChangeDirection = true;
}

void PacmanGhost::SetStateToVulnerable(){

    if (pState != GHOST_STATE_DEAD)
    {
        SetGhostState(GHOST_STATE_VULNERABLE);
    }
    
}

void PacmanGhost::SetGhostState(GhostState state){

    pState = state;

    switch (pState)
    {
    case GHOST_STATE_ALIVE:
        SetMovementDirection(GetMovementDirection());
        SetMovementSpeed(PACMAN_GHOST_MOVEMENT_SPEED);
        break;
    case GHOST_STATE_VULNERABLE:
        pSprite.SetAnimation("ghost_vulnerable", true);
        pVulnerabiltyTimer = 0;
        SetMovementSpeed(PACMAN_GHOST_VULN_MOVEMENT_SPEED);
        break;
    case GHOST_STATE_VULNERABLE_ENDING:
        pSprite.SetAnimation("ghost_vulnerable_ending", true);
        pVulnerabiltyTimer = 0;
        break;
      case GHOST_STATE_DEAD:
        SetMovementDirection(GetMovementDirection());
        SetMovementSpeed(PACMAN_GHOST_BACK_TO_PEN_SPEED);
        break;
    default:
        break;
    }
}
