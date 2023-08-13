#ifndef GAMES_PACMAN_PACMANGHOST__H__
#define GAMES_PACMAN_PACMANGHOST__H__

#include "pacmanactor.h"
#include "color.h"
#include "pacmangameutils.h"
#include "rectangle.h"

enum GhostName{
    BLINKY = 0,
    PINKY,
    INKY,
    CLYDE,
    NUM_GHOSTS
};

enum GhostState{
    GHOST_STATE_ALIVE = 0,
    GHOST_STATE_VULNERABLE,
    GHOST_STATE_VULNERABLE_ENDING,
    GHOST_STATE_DEAD
};

class PacmanGhost : public PacmanActor {

public:

    static const uint32_t VULNERABILITY_TIME = 6000;
    static const uint32_t VULNERABILITY_ENDING_TIME = 4000;

    PacmanGhost();

    virtual void Init (const SpriteSheet& spriteSheet, const std::string& animationsPath, const Vector2D& initialPos, uint32_t movementSpeed, bool updateSpriteOnMovement, const Color&spriteColor = White()) override;
    virtual void Update (uint32_t dt) override;

    virtual void SetMovementDirection(PacmanMovement dir) override;
    virtual void Stop() override;

    void EatenByPacman();
    void ResetToFirstPosition();
    void SetStateToVulnerable();

    inline bool IsDead() const {return pState == GHOST_STATE_DEAD;}
    inline bool IsVulnerable() const {return pState == GHOST_STATE_VULNERABLE || pState == GHOST_STATE_VULNERABLE_ENDING;}
    inline bool IsAlive() const {return pState == GHOST_STATE_ALIVE;}

    inline uint32_t GetPoints() const {return pPoints;}
    inline void LockCanChangeDirection() {pCanChangeDirection = false;}
    inline bool CanChangeDirection() const {return pCanChangeDirection;}

private:

    void SetGhostState(GhostState state);

    uint32_t pVulnerabiltyTimer;
    uint32_t pPoints;
    GhostState pState;

    bool pCanChangeDirection;
    Vector2D pInitialPos;

};

#endif  //!GAMES_PACMAN_PACMANGHOST__H__