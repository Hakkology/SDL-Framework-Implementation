#ifndef GAMES_PACMAN_PACMANGAMEUTILS__H__
#define GAMES_PACMAN_PACMANGAMEUTILS__H__

#include <vector>

#include "vector2D.h"

static const int PACMAN_MOVEMENT_SPEED = 50;
static const int PACMAN_GHOST_MOVEMENT_SPEED = 45;
static const int PACMAN_GHOST_VULN_MOVEMENT_SPEED = 25;
static const int PACMAN_GHOST_BACK_TO_PEN_SPEED = 100;

enum PacmanMovement
{
    PACMAN_MOVEMENT_NONE = 0,
    PACMAN_MOVEMENT_UP,
    PACMAN_MOVEMENT_LEFT,
    PACMAN_MOVEMENT_DOWN,
    PACMAN_MOVEMENT_RIGHT
};

Vector2D GetMovementVector (PacmanMovement direction);
PacmanMovement GetOppositeDirection(PacmanMovement direction);
std::vector <PacmanMovement> GetPerpendicularMovements(PacmanMovement direction);
std::vector <PacmanMovement> GetOtherDirections (PacmanMovement direction);

#endif  //!GAMES_PACMAN_PACMANGAMEUTILS__H__