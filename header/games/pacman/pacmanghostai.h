#ifndef GAMES_PACMAN_PACMANGHOSTAI__H__
#define GAMES_PACMAN_PACMANGHOSTAI__H__

#include <random>
#include <stdint.h>

#include "pacmanghost.h"
#include "pacmangameutils.h"

class PacmanLevel;
class PacmanPlayer;
class Screen;

enum GhostAIState{

    GHOST_AI_STATE_START = 0,
    GHOST_AI_STATE_IN_PEN,
    GHOST_AI_STATE_EXIT_PEN,
    GHOST_AI_STATE_CHASE,
    GHOST_AI_STATE_SCATTER,
    GHOST_AI_STATE_GO_TO_PEN
};

class PacmanGhostAI{

public:

    PacmanGhostAI();

    void Init(PacmanGhost& ghost, uint32_t lookAheadDistance, const Vector2D& scatterTarget, GhostName name);

    PacmanMovement Update(uint32_t dt, const PacmanPlayer& pacman, const PacmanLevel& level, const std::vector<PacmanGhost>& ghosts);
    void Draw (Screen& screen);

private:

    void SetState(GhostAIState state);
    inline void ChangeTarget(const Vector2D& target) {pTarget = target;}

    Vector2D GetChaseTarget(uint32_t dt, const PacmanPlayer& pacman, const PacmanLevel& level, const std::vector<PacmanGhost>& ghosts);

    Vector2D pScatterTarget;
    Vector2D pTarget;

    uint32_t pLookAheadDistance;
    uint64_t pTimer;

    PacmanGhost* pnoptrGhost;
    GhostName pName;
    GhostAIState pState;
    GhostAIState pLastState;


std::default_random_engine pAIRandomGenerator;

};

#endif  //!GAMES_PACMAN_PACMANGHOSTAI__H__