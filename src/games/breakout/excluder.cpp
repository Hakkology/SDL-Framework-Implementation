#include "excluder.h"

void Excluder::Init(const Rectangle &rect, bool reverseNormals){

    bRectangle = rect;
    bReverseNormals = reverseNormals;
    SetupEdges();
}

bool Excluder::HasCollided(const Rectangle &rect, BoundaryEdge &edge) const
{
    if (bRectangle.Intersects(rect))
    {
        float yMin = bRectangle.GetTopLeftPoint().GetY() >= (rect.GetTopLeftPoint().GetY()) ? bRectangle.GetTopLeftPoint().GetY() : rect.GetTopLeftPoint().GetY();
        float yMax = bRectangle.GetBottomRightPoint().GetY() <= rect.GetBottomRightPoint().GetY() ? bRectangle.GetBottomRightPoint().GetY() : rect.GetBottomRightPoint().GetY();

        float ySize = yMax - yMin;

        float xMin = bRectangle.GetTopLeftPoint().GetX() >= rect.GetTopLeftPoint().GetX() ? bRectangle.GetTopLeftPoint().GetX() : rect.GetTopLeftPoint().GetX();
        float xMax = bRectangle.GetBottomRightPoint().GetX() <= rect.GetBottomRightPoint().GetX() ? bRectangle.GetBottomRightPoint().GetX() : rect.GetBottomRightPoint().GetX();

        float xSize = xMax - xMin;

        if (xSize > ySize)
        {
            if (rect.GetCenterPoint().GetY() > bRectangle.GetCenterPoint().GetY())
            {
                edge = bEdges[BOTTOM_EDGE];
            }
            else
            {
                edge = bEdges[TOP_EDGE];
            }
        }
        else
        {
            if (rect.GetCenterPoint().GetX() < bRectangle.GetCenterPoint().GetX())
            {
                edge = bEdges [LEFT_EDGE];
            }
            else
            {
                edge = bEdges [RIGHT_EDGE];
            }
        }
        return true;
    }
    return false;
}

Vector2D Excluder::GetCollisionOffset(const Rectangle &rect) const
{
    BoundaryEdge edge;
    Vector2D offset = Vector2D::Zero;

    if (HasCollided(rect, edge))
    {
        float yMin = bRectangle.GetTopLeftPoint().GetY() >= (rect.GetTopLeftPoint().GetY()) ? bRectangle.GetTopLeftPoint().GetY() : rect.GetTopLeftPoint().GetY();
        float yMax = bRectangle.GetBottomRightPoint().GetY() <= rect.GetBottomRightPoint().GetY() ? bRectangle.GetBottomRightPoint().GetY() : rect.GetBottomRightPoint().GetY();

        float ySize = yMax - yMin;

        float xMin = bRectangle.GetTopLeftPoint().GetX() >= rect.GetTopLeftPoint().GetX() ? bRectangle.GetTopLeftPoint().GetX() : rect.GetTopLeftPoint().GetX();
        float xMax = bRectangle.GetBottomRightPoint().GetX() <= rect.GetBottomRightPoint().GetX() ? bRectangle.GetBottomRightPoint().GetX() : rect.GetBottomRightPoint().GetX();

        float xSize = xMax - xMin;

        if (!IsEqual(edge.normal.GetY(), 0))
        {
            offset = edge.normal * (ySize +1);
        }
        else
        {
            offset = edge.normal * (xSize +1);
        }
    }
    return offset;
}

void Excluder::MoveBy(const Vector2D &delta){

    bRectangle.MoveBy(delta);
    SetupEdges();
}

void Excluder::MoveTo(const Vector2D &point){

    bRectangle.MoveTo(point);
    SetupEdges();
}

const BoundaryEdge &Excluder::GetEdge(EdgeType edge) const
{
    assert(edge != NUM_EDGES);
    return bEdges[edge];
}

void Excluder::SetupEdges(){

    bEdges[TOP_EDGE].edge = {bRectangle.GetTopLeftPoint().GetX(), bRectangle.GetTopLeftPoint().GetY(), 
                            bRectangle.GetBottomRightPoint().GetX(), bRectangle.GetTopLeftPoint().GetY()};
    bEdges[TOP_EDGE].normal = UP_DIR;

    bEdges[LEFT_EDGE].edge = {bRectangle.GetTopLeftPoint().GetX(), bRectangle.GetTopLeftPoint().GetY(), 
                            bRectangle.GetTopLeftPoint().GetX(), bRectangle.GetBottomRightPoint().GetY()};
    bEdges[LEFT_EDGE].normal = LEFT_DIR;

    bEdges[BOTTOM_EDGE].edge = {bRectangle.GetTopLeftPoint().GetX(), bRectangle.GetBottomRightPoint().GetY(), 
                            bRectangle.GetBottomRightPoint().GetX(), bRectangle.GetBottomRightPoint().GetY()};
    bEdges[BOTTOM_EDGE].normal = DOWN_DIR;

    bEdges[RIGHT_EDGE].edge = {bRectangle.GetBottomRightPoint().GetX(), bRectangle.GetTopLeftPoint().GetY(), 
                            bRectangle.GetBottomRightPoint().GetX(), bRectangle.GetBottomRightPoint().GetY()};
    bEdges[RIGHT_EDGE].normal = RIGHT_DIR;

    if (bReverseNormals)
    {
        for (auto& edge:bEdges)
        {
            edge.normal = -edge.normal;
        }
    }
}
