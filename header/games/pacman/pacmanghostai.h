#ifndef GAMES_PACMAN_PACMANGHOSTAI__H__
#define GAMES_PACMAN_PACMANGHOSTAI__H__

#include <random>

#include "pacmanghost.h"
#include "pacmangameutils.h"

class PacmanLevel;
class Screen;

class PacmanGhostAI{

public:

    PacmanGhostAI();

    void Init(PacmanGhost& ghost, GhostName name);

    PacmanMovement Update(uint32_t dt, const PacmanLevel& level);
    void Draw (Screen& screen);

private:

PacmanGhost* pnoptrGhost;
GhostName pName;

std::default_random_engine pAIRandomGenerator;

};

#endif  //!GAMES_PACMAN_PACMANGHOSTAI__H__