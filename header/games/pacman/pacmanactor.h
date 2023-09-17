#ifndef GAMES_PACMAN_ACTOR__H__
#define GAMES_PACMAN_ACTOR__H__

#include <string>
#include <stdint.h>

#include "animatedsprite.h"
#include "vector2D.h"
#include "pacmangameutils.h"
#include "rectangle.h"
#include "color.h"
#include "actor.h"

class Screen;
class SpriteSheet;

class PacmanActor : public Actor
{

public:
    virtual ~PacmanActor() {}
    virtual void Init (const SpriteSheet& spriteSheet, const std::string& animationsPath, const Vector2D& initialPos, uint32_t movementSpeed, bool updateSpriteOnMovement, const Color&spriteColor = White());
    virtual void Update (uint32_t dt);
    virtual void Draw (Screen& screen);

    virtual void Stop();
    Rectangle GetEatingBoundingBox() const;

    virtual inline void SetMovementDirection(PacmanMovement direction) {pMovementDirection = direction;} 

    inline bool isFinishedAnimation() const {return pSprite.IsFinishedPlayingAnimation();}
    inline const Rectangle GetBoundingBox() const {return pSprite.GetBoundingBox();}
    inline void MoveBy(const Vector2D& delta) {pSprite.MoveBy(delta);}
    inline void MoveTo(const Vector2D& position) {pSprite.SetPosition(position);}
    inline Vector2D Position() const {return pSprite.Position();}
    inline PacmanMovement GetMovementDirection() const {return pMovementDirection;}
    inline const Color& GetSpriteColor() const {return pSprite.GetColor();}
    
protected:

    inline void ResetDelta() {pDelta = Vector2D::Zero;}
    inline void SetMovementSpeed(uint32_t movementSpeed) {pMovementSpeed = movementSpeed;}

    void SetAnimation (const std::string& animationName, bool looped);

    AnimatedSprite pSprite;

private:

    Vector2D pDelta;
    PacmanMovement pMovementDirection;

    uint32_t pMovementSpeed;
    bool pUpdateSpriteOnUpdate;
};



#endif  //!GAMES_PACMAN_ACTOR__H__