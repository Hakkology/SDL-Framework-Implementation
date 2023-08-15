#include <cassert>
#include <algorithm>

#include "pacmanghostai.h"
#include "screen.h"
#include "pacmanlevel.h"
#include "pacmanplayer.h"
#include "circle.h"

namespace{

    const uint32_t PEN_WAIT_DURATION = 5000;
    const uint32_t SCATTER_MODE_DURATION = 10000;
}

PacmanGhostAI::PacmanGhostAI():pnoptrGhost(nullptr){

}

void PacmanGhostAI::Init(PacmanGhost& ghost, uint32_t lookAheadDistance, const Vector2D& scatterTarget, const Vector2D& ghostPenTarget, const Vector2D& ghostExitPenPosition, GhostName name){

    pGhostPenTarget = ghostPenTarget;
    pGhostExitPenPosition = ghostExitPenPosition;

    pScatterTarget = scatterTarget;
    pLookAheadDistance = lookAheadDistance;
    pnoptrGhost = &ghost;
    pName = name;

    std::random_device r;
    pAIRandomGenerator.seed(r());

    pTimer = 0;
    SetState(GHOST_AI_STATE_SCATTER);
    pLastState = GHOST_AI_STATE_SCATTER;
}

PacmanMovement PacmanGhostAI::Update(uint32_t dt, const PacmanPlayer& pacman, const PacmanLevel &level, const std::vector<PacmanGhost>& ghosts){

    if (pnoptrGhost)
    {

        if (pState == GHOST_AI_STATE_START)
        {
            return PACMAN_MOVEMENT_NONE;
        }
        
        if (pState == GHOST_AI_STATE_IN_PEN)
        {
            pTimer += dt;

            if (pTimer >= PEN_WAIT_DURATION)
            {
                SetState(GHOST_AI_STATE_EXIT_PEN);
            }

            return PACMAN_MOVEMENT_NONE;
        }
        
        if (pState == GHOST_AI_STATE_GO_TO_PEN && pnoptrGhost->Position() == pGhostPenTarget)
        {
            SetState(GHOST_AI_STATE_IN_PEN);
            pnoptrGhost -> SetGhostState(GHOST_STATE_ALIVE);
            return PACMAN_MOVEMENT_NONE;
        }

        if (pState == GHOST_AI_STATE_EXIT_PEN && pnoptrGhost->Position() == pGhostExitPenPosition)
        {
            SetState(GHOST_AI_STATE_SCATTER);
        }

        if (pState == GHOST_AI_STATE_SCATTER)
        {
            pTimer +=dt;
            
            if (pTimer >= SCATTER_MODE_DURATION)
            {
                SetState(GHOST_AI_STATE_CHASE);
            }
        }
        
        PacmanMovement currentDirection = pnoptrGhost->GetMovementDirection();

        std::vector<PacmanMovement> tempDirections;
        std::vector<PacmanMovement> possibleDirections;

        possibleDirections = GetPerpendicularMovements(currentDirection);

        if (currentDirection != PACMAN_MOVEMENT_NONE)
        {
            possibleDirections.push_back(currentDirection);
        }

        for(const auto& pDirections : possibleDirections){

            tempDirections.push_back(pDirections);
        }
        
        possibleDirections.clear();

        for(const auto& direction : tempDirections){

            if (!level.WillCollide(*pnoptrGhost, *this, direction))
            {
                possibleDirections.push_back(direction);
            }
        }

        assert(possibleDirections.size() >= 1 && "Im lost, help me!");

        std::sort(possibleDirections.begin(), possibleDirections.end(), 
        [] (const PacmanMovement& direction1, const PacmanMovement& direction2){
            
            return direction1 < direction2;
        });

        if (pnoptrGhost->IsVulnerable() && (pState == GHOST_AI_STATE_SCATTER || pState == GHOST_AI_STATE_CHASE))
        {
            std::uniform_int_distribution<size_t> distribution(0, possibleDirections.size()-1);
            return possibleDirections[static_cast<int>(distribution(pAIRandomGenerator))];
        }

        if (pState == GHOST_AI_STATE_CHASE)
        {
            ChangeTarget(GetChaseTarget(dt, pacman, level, ghosts));
        }
        
        PacmanMovement directionToGoIn = PACMAN_MOVEMENT_NONE;

        uint32_t lowestDistance = UINT32_MAX;

        for(const auto& direction: possibleDirections){

            Vector2D movementVector = GetMovementVector(direction) * pLookAheadDistance;
            Rectangle bbox = pnoptrGhost->GetBoundingBox();
            bbox.MoveBy(movementVector);

            uint32_t distanceToTarget = bbox.GetCenterPoint().Distance(pTarget);

            if (distanceToTarget < lowestDistance)
            {
                directionToGoIn = direction;
                lowestDistance = distanceToTarget;
            }
        }

        assert(directionToGoIn != PACMAN_MOVEMENT_NONE);
        return directionToGoIn;
    }
    return PACMAN_MOVEMENT_NONE;
}

void PacmanGhostAI::Draw(Screen &screen){

    if (pnoptrGhost)
    {

        Circle targetCircle = Circle(pTarget, 4);
        screen.Draw(targetCircle, pnoptrGhost->GetSpriteColor(), true, pnoptrGhost->GetSpriteColor());

        Rectangle bbox = pnoptrGhost->GetBoundingBox();
        bbox.MoveBy(GetMovementVector(pnoptrGhost->GetMovementDirection())* pnoptrGhost->GetBoundingBox().GetWidth());
    
        Color c = Color(pnoptrGhost->GetSpriteColor().GetRed(), pnoptrGhost->GetSpriteColor().GetGreen(),
                        pnoptrGhost->GetSpriteColor().GetBlue(), 200);

        screen.Draw (bbox, pnoptrGhost->GetSpriteColor(), true, c);
    }
}

void PacmanGhostAI::GhostDelegateGhostStateChangedTo(GhostState lastState, GhostState state){

    if (pnoptrGhost && pnoptrGhost->IsReleased() 
                    && (lastState == GHOST_STATE_VULNERABLE || lastState == GHOST_STATE_VULNERABLE_ENDING 
                    && !(IsInPen() || WantsToLeavePen())))
    {
        pnoptrGhost->SetMovementDirection(GetOppositeDirection(pnoptrGhost->GetMovementDirection()));
    }
    
    if (state == GHOST_STATE_DEAD)
    {
        SetState(GHOST_AI_STATE_GO_TO_PEN);
    }
}

void PacmanGhostAI::GhostWasReleasedFromPen(){

    if (pState == GHOST_AI_STATE_START)
    {
        SetState(GHOST_AI_STATE_EXIT_PEN);
    }
}

void PacmanGhostAI::GhostWasResetToFirstPosition(){

}

void PacmanGhostAI::SetState(GhostAIState state){

    if (pState == GHOST_AI_STATE_SCATTER || pState == GHOST_AI_STATE_CHASE)
    {
        pLastState = pState;
    }
    
    pState = state;

    switch (state)
    {
    case GHOST_AI_STATE_IN_PEN:
        pTimer = 0;
        break;
    case GHOST_AI_STATE_GO_TO_PEN:

        break;
    case GHOST_AI_STATE_EXIT_PEN:
        {
            Vector2D target = {pGhostPenTarget.GetX() + pnoptrGhost->GetBoundingBox().GetWidth()/2, pGhostPenTarget.GetY() - pnoptrGhost->GetBoundingBox().GetHeight()/2};
            ChangeTarget(target);
        }
        break;
    case GHOST_AI_STATE_SCATTER:
        pTimer = 0;
        ChangeTarget(pScatterTarget);
        break;
    default:
        break;
    }
}

Vector2D PacmanGhostAI::GetChaseTarget(uint32_t dt, const PacmanPlayer &pacman, const PacmanLevel &level, const std::vector<PacmanGhost> &ghosts)
{
    Vector2D target;

    switch (pName)
    {

    case BLINKY:
        target = pacman.GetBoundingBox().GetCenterPoint();
        break;

    case PINKY:
        target = pacman.GetBoundingBox().GetCenterPoint() + GetMovementVector(pacman.GetMovementDirection()) * pacman.GetBoundingBox().GetWidth() * 2.0f;
        break;
    
    case INKY:
        {
            Vector2D pacmanOffsetPoint = pacman.GetBoundingBox().GetCenterPoint() + 
            (GetMovementVector(pacman.GetMovementDirection()) * pacman.GetBoundingBox().GetWidth());
            target = (pacmanOffsetPoint - ghosts[BLINKY].GetBoundingBox().GetCenterPoint()) * 2 + 
            ghosts[BLINKY].GetBoundingBox().GetCenterPoint();
        }
        break;
    case CLYDE:
        {
            auto distanceToPacman = pnoptrGhost->GetBoundingBox().GetCenterPoint().Distance(pacman.GetBoundingBox().GetCenterPoint());
            if (distanceToPacman > pacman.GetBoundingBox().GetWidth() *4)
            {
                target = pacman.GetBoundingBox().GetCenterPoint();
            }
            else
            {
                target = pScatterTarget;
            }
        }
        break;
    }

    return target;
}
