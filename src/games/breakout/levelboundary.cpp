#include "levelboundary.h"

LevelBoundary::LevelBoundary(const Rectangle &boundary){

    bIncluder.Init(boundary, true);
}

bool LevelBoundary::HasCollided(const Ball &ball, BoundaryEdge &edge){

    for (int i = 0; i < NUM_EDGES; ++i)
    {
        BoundaryEdge collisionEdge = bIncluder.GetEdge(static_cast<EdgeType>(i));

        if (HasCollidedWithEdge(ball, collisionEdge))
        {
            edge = collisionEdge;
            return true;
        }
    }

    return false;
}

bool LevelBoundary::HasCollidedWithEdge(const Ball &ball, const BoundaryEdge &edge) const{

    return edge.edge.MinDistanceFrom(ball.GetPosition()) < ball.GetRadius();
}
