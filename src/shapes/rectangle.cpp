#include "rectangle.h"

Rectangle::Rectangle() : Rectangle(Vector2D::Zero,Vector2D::Zero){

}

Rectangle::Rectangle(const Vector2D& topLeft, unsigned int width, unsigned int height){

    sPoints.push_back(topLeft);
    sPoints.push_back(Vector2D(topLeft.GetX() + width -1, topLeft.GetY() + height -1));
}

Rectangle::Rectangle(const Vector2D topLeft, const Vector2D bottomRight){

    sPoints.push_back(topLeft);
    sPoints.push_back(bottomRight);
}

float Rectangle::GetWidth() const{

    return GetBottomRightPoint().GetX() - GetTopLeftPoint().GetX() + 1;
}
float Rectangle::GetHeight() const{

    return GetBottomRightPoint().GetY() - GetTopLeftPoint().GetY() +1 ;
}

void Rectangle::MoveTo(const Vector2D& position){

    float width = GetWidth();
    float height = GetHeight();

    SetTopLeftPoint(position);
    SetBottomRightPoint(Vector2D(position.GetX() + width -1, position.GetY() + height -1));
}

Vector2D Rectangle::GetCenterPoint() const{

    return Vector2D((GetTopLeftPoint().GetX() + GetBottomRightPoint().GetX()) / 2.0f, (GetTopLeftPoint().GetY() + GetBottomRightPoint().GetY()) / 2.0f);
}

bool Rectangle::Intersects(const Rectangle& otherRectangle) const{

    return !(otherRectangle.GetBottomRightPoint().GetX() < GetTopLeftPoint().GetX() ||
            otherRectangle.GetTopLeftPoint().GetX() > GetBottomRightPoint().GetX() ||
            otherRectangle.GetBottomRightPoint().GetY() < GetTopLeftPoint().GetY() ||
            otherRectangle.GetTopLeftPoint().GetY() > GetBottomRightPoint().GetY());
}

bool Rectangle::ContainsPoint(const Vector2D& point) const{

    bool withinX = point.GetX() >= GetTopLeftPoint().GetX() && point.GetX() <= GetBottomRightPoint().GetX();
    bool withinY = point.GetY() >= GetTopLeftPoint().GetY() && point.GetY() <= GetBottomRightPoint().GetY();

    return withinX && withinY;
}

Rectangle Rectangle::Inset (const Rectangle& rect, const Vector2D& insets){

    return Rectangle(rect.GetTopLeftPoint() + insets, rect.GetWidth() - 2*insets.GetX(), rect.GetHeight() - 2*insets.GetY());
}

std::vector<Vector2D> Rectangle::GetPoints() const{

    std::vector<Vector2D> points;
    
    points.push_back(sPoints[0]);
    points.push_back(Vector2D(sPoints[1].GetX(), sPoints[0].GetY()));
    points.push_back(sPoints[1]);
    points.push_back(Vector2D(sPoints[0].GetX(), sPoints[1].GetY()));

    return points;
}