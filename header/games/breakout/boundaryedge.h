#ifndef GAMES_BOUNDARYEDGE_H
#define GAMES_BOUNDARYEDGE_H

#include "vector2D.h"
#include "line2D.h"
#include "constants.h"

enum EdgeType{

    BOTTOM_EDGE = 0,
    TOP_EDGE,
    LEFT_EDGE,
    RIGHT_EDGE,
    NUM_EDGES
};

struct BoundaryEdge {

    Vector2D normal;
    Line2D edge;
};

#endif