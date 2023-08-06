#ifndef GAMES_EXCLUDER_H
#define GAMES_EXCLUDER_H

#include <cmath>
#include <cassert>

#include "rectangle.h"
#include "boundaryedge.h"
#include "utilities.h"


class Excluder {

public:

    virtual ~Excluder() {}

    void Init(const Rectangle& rect, bool reverseNormals = false);
    bool HasCollided (const Rectangle& rect, BoundaryEdge& edge) const;
    Vector2D GetCollisionOffset (const Rectangle& rect) const;

    inline const Rectangle& GetRectangle() const {return bRectangle;}
    void MoveBy(const Vector2D& delta);
    void MoveTo(const Vector2D& point);
    const BoundaryEdge& GetEdge(EdgeType edge) const;

private:

    void SetupEdges();
    Rectangle bRectangle;
    BoundaryEdge bEdges [NUM_EDGES];
    bool bReverseNormals;
};

#endif