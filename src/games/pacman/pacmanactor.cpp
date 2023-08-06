#include <cmath>

#include "pacmanactor.h"
#include "utilities.h"

void PacmanActor::Init(const SpriteSheet &spriteSheet, const std::string &animationsPath, const Vector2D& initialPos, uint32_t movementSpeed, bool updateSpriteOnMovement, const Color &spriteColor){

    pMovementDirection = PACMAN_MOVEMENT_NONE;
    pSprite.Init(animationsPath, spriteSheet, spriteColor);
    pUpdateSpriteOnUpdate = updateSpriteOnMovement;
    pMovementSpeed = movementSpeed;
    pDelta = Vector2D::Zero;
    pSprite.SetPosition(initialPos);
}

// for updating the position and animation of the Pacman actor based on its current movement direction and movement speed
void PacmanActor::Update(uint32_t dt){

    if (pMovementDirection != PACMAN_MOVEMENT_NONE)
    {
        Vector2D delta = Vector2D::Zero;
        delta = GetMovementVector(pMovementDirection) * pMovementSpeed;
        pDelta += delta * MillisecondstoSeconds(dt);

        if (fabsf(pDelta.GetX()) >= 1)
        {
            int dx = int(fabsf(pDelta.GetX()));

            if (pDelta.GetX() < 0)
            {
                pSprite.MoveBy(Vector2D(-dx,0));
                pDelta.SetX(pDelta.GetX() + dx);
            }
            else
            {
                pSprite.MoveBy(Vector2D(dx,0));
                pDelta.SetX(pDelta.GetX() - dx);
            }
        }
        else if(fabsf(pDelta.GetY()) >= 1)
        {
            int dy = int(fabsf(pDelta.GetY()));

            if (pDelta.GetY() < 0)
            {
                pSprite.MoveBy(Vector2D(0,-dy));
                pDelta.SetY(pDelta.GetY() + dy);
            }
            else
            {
                pSprite.MoveBy(Vector2D(0,dy));
                pDelta.SetY(pDelta.GetY() - dy);
            }
        }
        pSprite.Update(dt);
    }

    if (pUpdateSpriteOnUpdate && pMovementDirection == PACMAN_MOVEMENT_NONE)
    {
        pSprite.Update(dt);
    }
}

void PacmanActor::Draw(Screen &screen){

    pSprite.Draw(screen);
}

void PacmanActor::Stop(){

    SetMovementDirection(PACMAN_MOVEMENT_NONE);
    pSprite.Stop();
}

Rectangle PacmanActor::GetEatingBoundingBox() const{

    return Rectangle::Inset(GetBoundingBox(), Vector2D(3,3));
}

void PacmanActor::SetAnimation(const std::string &animationName, bool looped){

    pSprite.SetAnimation(animationName, looped);
}
