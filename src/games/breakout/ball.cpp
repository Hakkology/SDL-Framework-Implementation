#include "ball.h"

Ball::Ball():Ball(Vector2D::Zero, ballRadius){

}

Ball::Ball(const Vector2D &pos, float radius): bBoundingBox(pos-Vector2D(radius, radius), radius*2.0f, radius*2.0f), bVelocity(Vector2D::Zero){

}

void Ball::Update(uint32_t dt){

    bBoundingBox.MoveBy(bVelocity * MillisecondstoSeconds(dt));
}

void Ball::Draw(Screen &screen){

    Circle circle = {bBoundingBox.GetCenterPoint(), GetRadius()};
    screen.Draw(circle, Red(), true, Red());
}

void Ball::Bounce(const BoundaryEdge &edge){

    Vector2D normal = edge.normal;
    float dotProduct = bVelocity.Dot(normal);
    Vector2D reflection = bVelocity - (normal * (2.0f * dotProduct));

    bVelocity = reflection;
}

void Ball::MakeFlushWithEdge(const BoundaryEdge &edge, Vector2D &pointOnEdge, bool limitToEdge){

    if (edge.normal == DOWN_DIR)
    {
        bBoundingBox.MoveTo(Vector2D(bBoundingBox.GetTopLeftPoint().GetX(), edge.edge.GetP0().GetY() + edge.normal.GetY()));
    }
    else if (edge.normal == UP_DIR)
    {
        bBoundingBox.MoveTo(Vector2D(bBoundingBox.GetTopLeftPoint().GetX(), edge.edge.GetP0().GetY() - bBoundingBox.GetHeight()));
    }
    else if (edge.normal == RIGHT_DIR)
    {
        bBoundingBox.MoveTo(Vector2D(edge.edge.GetP0().GetX() + edge.normal.GetX(), bBoundingBox.GetTopLeftPoint().GetY()));
    }
    else if (edge.normal == LEFT_DIR)
    {
        bBoundingBox.MoveTo(Vector2D(edge.edge.GetP0().GetX() - bBoundingBox.GetWidth(), bBoundingBox.GetTopLeftPoint().GetY()));
    }

    pointOnEdge = edge.edge.ClosestPoint(bBoundingBox.GetCenterPoint(), limitToEdge);
}

void Ball::MoveTo(const Vector2D &point){

    bBoundingBox.MoveTo(point - Vector2D(GetRadius(), GetRadius()));
}
