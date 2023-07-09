#include "triangle.h"

Triangle::Triangle(): Triangle(Vector2D::Zero,Vector2D::Zero,Vector2D::Zero)
{

}

Triangle::Triangle(const Vector2D& p0, const Vector2D& p1, const Vector2D& p2)
{
    sPoints.push_back(p0);
    sPoints.push_back(p1);
    sPoints.push_back(p2);
}

Vector2D Triangle::GetCenterPoint() const
{
    return Vector2D((sPoints[0].GetX() + sPoints[1].GetX() + sPoints[2].GetX())/3.0f,
                    (sPoints[0].GetY() + sPoints[1].GetY() + sPoints[2].GetY())/3.0f);
}

float Triangle::Area() const
{
    return Area(GetP0(), GetP1(), GetP2());
}

float Triangle::Area(const Vector2D& p0, const Vector2D& p1, const Vector2D& p2) const
{
    return fabsf((p0.GetX()*(p1.GetY() - p2.GetY()) + p1.GetX() * (p2.GetY() - p0.GetY()) + p2.GetX() *(p0.GetY() - p1.GetY())) / 2.0f);
}

float Triangle::ContainsPoint(const Vector2D &p) const
{
    float thisArea = Area();

    float a1 = Area(p, GetP1(), GetP2());
    float a2 = Area(GetP0(), p, GetP2());
    float a3 = Area(GetP0(), GetP1(), p);

    return IsEqual(thisArea, a1 + a2 + a3);
}
