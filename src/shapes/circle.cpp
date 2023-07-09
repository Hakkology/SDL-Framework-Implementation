#include "circle.h"

Circle::Circle(){


}

Circle::Circle(const Vector2D& center, float radius){

    sPoints.push_back(center);
}

bool Circle::Intersects(const Circle& otherCircle){

    return GetCenterPoint().Distance(otherCircle.GetCenterPoint()) < (cRadius + otherCircle.cRadius);
}

bool Circle::ContainsPoint(const Vector2D& point) const{

    return IsLessThanOrEqual((GetCenterPoint().Distance(point)), cRadius);
}
