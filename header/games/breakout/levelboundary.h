#ifndef GAMES_LEVELBOUNDARY_H
#define GAMES_LEVELBOUNDARY_H

#include "excluder.h"
#include "ball.h"
#include "boundaryedge.h"

class Rectangle;

class LevelBoundary {

public:

    LevelBoundary(const Rectangle& boundary);
    bool HasCollided (const Ball& ball, BoundaryEdge& edge);
    
    inline const Rectangle& GetBoundaryRectangle() const {return bIncluder.GetRectangle();}


private:

    bool HasCollidedWithEdge(const Ball& ball, const BoundaryEdge& edge) const;
    Excluder bIncluder;
};

#endif