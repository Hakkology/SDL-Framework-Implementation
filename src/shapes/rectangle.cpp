#include "rectangle.h"

Rectangle::Rectangle() : Rectangle(Vector2D::Zero,Vector2D::Zero){

}

Rectangle::Rectangle(const Vector2D& topLeft, unsigned int width, unsigned int height){

    sPoints.push_back(topLeft);
    sPoints.push_back(Vector2D(topLeft.GetX() + width -1, topLeft.GetY() + height -1));
}

Rectangle::Rectangle(const Vector2D topLeft, const Vector2D bottomRight){

}

float Rectangle::GetWidth() const{

}
float Rectangle::GetHeight() const{

}

void Rectangle::MoveTo(const Vector2D& position){

}

Vector2D Rectangle::GetCenterPoint() const{

}

bool Rectangle::Intersects(const Rectangle& otherRectangle){

}

bool Rectangle::ContainsPoint(const Vector2D& point) const{

}

Rectangle Rectangle::Inset (const Rectangle& rect, Vector2D insets){

}

std::vector<Vector2D> Rectangle::GetPoints() const{

}