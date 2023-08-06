#ifndef GAMES_PACMAN_PACMANGAMEUTILS__H__
#define GAMES_PACMAN_PACMANGAMEUTILS__H__

#include <vector>

#include "vector2D.h"

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

#endif  //!GAMES_PACMAN_PACMANGAMEUTILS__H__