#include <cassert>
#include <algorithm>

#include "pacmanghostai.h"
#include "screen.h"
#include "pacmanlevel.h"


PacmanGhostAI::PacmanGhostAI():pnoptrGhost(nullptr){

}

void PacmanGhostAI::Init(PacmanGhost &ghost, GhostName name){

    pnoptrGhost = &ghost;
    pName = name;

    std::random_device r;
    pAIRandomGenerator.seed(r());
}

PacmanMovement PacmanGhostAI::Update(uint32_t dt, const PacmanLevel &level){

    if (pnoptrGhost)
    {
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

            if (!level.WillCollide(pnoptrGhost->GetBoundingBox(), direction))
            {
                possibleDirections.push_back(direction);
            }
        }

        assert(possibleDirections.size() >= 1 && "Im lost, help me!");

        std::sort(possibleDirections.begin(), possibleDirections.end(), 
        [] (const PacmanMovement& direction1, const PacmanMovement& direction2){
            
            return direction1 < direction2;
        });

        std::uniform_int_distribution<size_t> distribution(0, possibleDirections.size()-1);

        return possibleDirections[static_cast<int>(distribution(pAIRandomGenerator))];

        return PACMAN_MOVEMENT_NONE;
    }
    
}

void PacmanGhostAI::Draw(Screen &screen){

    if (pnoptrGhost)
    {
        Rectangle bbox = pnoptrGhost->GetBoundingBox();

        bbox.MoveBy(GetMovementVector(pnoptrGhost->GetMovementDirection())* pnoptrGhost->GetBoundingBox().GetWidth());
    
        Color c = Color(pnoptrGhost->GetSpriteColor().GetRed(), pnoptrGhost->GetSpriteColor().GetGreen(),
                        pnoptrGhost->GetSpriteColor().GetBlue(), 200);

        screen.Draw (bbox, pnoptrGhost->GetSpriteColor(), true, c);
    }
}
