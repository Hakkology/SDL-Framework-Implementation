#include "pacmangameutils.h"
#include "constants.h"

Vector2D GetMovementVector(PacmanMovement direction){

    if (direction == PACMAN_MOVEMENT_LEFT)
    {
        return LEFT_DIR;
    }
    else if (direction == PACMAN_MOVEMENT_DOWN)
    {
        return DOWN_DIR;
    }
    else if (direction == PACMAN_MOVEMENT_RIGHT)
    {
        return RIGHT_DIR;
    }
    else if (direction == PACMAN_MOVEMENT_UP)
    {
        return UP_DIR;
    }

    return Vector2D::Zero;
    
}

PacmanMovement GetOppositeDirection(PacmanMovement direction) {

    if (direction == PACMAN_MOVEMENT_LEFT)
    {
        return PACMAN_MOVEMENT_RIGHT;
    }
    else if (direction == PACMAN_MOVEMENT_DOWN)
    {
        return PACMAN_MOVEMENT_UP;
    }
    else if (direction == PACMAN_MOVEMENT_RIGHT)
    {
        return PACMAN_MOVEMENT_RIGHT;
    }
    else if (direction == PACMAN_MOVEMENT_UP)
    {
        return PACMAN_MOVEMENT_DOWN;
    }

    return PACMAN_MOVEMENT_NONE;
}

std::vector<PacmanMovement> GetPerpendicularMovements(PacmanMovement direction){

    std::vector<PacmanMovement> perpendicularDirections;

    if (direction == PACMAN_MOVEMENT_UP || direction == PACMAN_MOVEMENT_DOWN)
    {
        perpendicularDirections.push_back(PACMAN_MOVEMENT_LEFT);
        perpendicularDirections.push_back(PACMAN_MOVEMENT_RIGHT);
    }
    else if (direction == PACMAN_MOVEMENT_RIGHT|| direction == PACMAN_MOVEMENT_LEFT)
    {
        perpendicularDirections.push_back(PACMAN_MOVEMENT_UP);
        perpendicularDirections.push_back(PACMAN_MOVEMENT_DOWN);
    }
    else if (direction == PACMAN_MOVEMENT_NONE)
    {
        perpendicularDirections.push_back(PACMAN_MOVEMENT_UP);
        perpendicularDirections.push_back(PACMAN_MOVEMENT_LEFT);
        perpendicularDirections.push_back(PACMAN_MOVEMENT_DOWN);
        perpendicularDirections.push_back(PACMAN_MOVEMENT_RIGHT);
    }

    return perpendicularDirections;
}

std::vector<PacmanMovement> GetOtherDirections(PacmanMovement direction)
{
    std::vector<PacmanMovement> directions;

    for (int dir = PacmanMovement::PACMAN_MOVEMENT_NONE; dir <= PACMAN_MOVEMENT_RIGHT; ++dir)
    {
        if (dir != direction)
        {
            directions.push_back(static_cast<PacmanMovement>(dir));
        }
    }
    return directions;
}
