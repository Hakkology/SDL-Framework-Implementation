#ifndef GAMES_PACMAN_PACMANPLAYER__H__
#define GAMES_PACMAN_PACMANPLAYER__H__

#include <stdint.h>

#include "pacmanactor.h"

class Screen;
class SpriteSheet;

class PacmanPlayer : public PacmanActor
{

public:
    virtual void Init (const SpriteSheet& spriteSheet, const std::string& animationPath, 
                       const Vector2D& initialPos, uint32_t movementSpeed, bool updateSpriteOnMovement, const Color& spriteColor = White()) override;
    virtual void Update (uint32_t dt) override;
    virtual void SetMovementDirection(PacmanMovement movementDir) override;

    void ResetToFirstAnimation();
    void EatenByGhost();
    void ResetScore();
    void AteItem(uint32_t value);
    void AteGhost (uint32_t value);
    
    inline void ResetGhostEatenMultiplier() {pGhostMultiplier = 1;}
    inline uint32_t Score() const {return pScore;}


private:
    
    void AddToScore(uint32_t value);

    uint32_t pScore;
    uint32_t pGhostMultiplier;
    bool pIsDying;
};

#endif  //!GAMES_PACMAN_PACMANPLAYER__H__