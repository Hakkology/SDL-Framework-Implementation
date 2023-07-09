#include "circle.h"

Circle::Circle(): Circle(Vector2D::Zero, 0){


}

Circle::Circle(const Vector2D& center, float radius):cRadius(radius){

    sPoints.push_back(center);
}

bool Circle::Intersects(const Circle& otherCircle){

    return GetCenterPoint().Distance(otherCircle.GetCenterPoint()) < (cRadius + otherCircle.cRadius);
}

bool Circle::ContainsPoint(const Vector2D& point) const{

    return IsLessThanOrEqual((GetCenterPoint().Distance(point)), cRadius);
}
