#include "line2D.h"

Line2D::Line2D(): vP0(Vector2D::Zero), vP1(Vector2D::Zero){

}

Line2D::Line2D(float x0, float y0, float x1, float y1){

    vP0 = Vector2D(x0, y0);
    vP1 = Vector2D(x1, y1);
}

Line2D::Line2D(const Vector2D& p0, const Vector2D& p1){

    vP0 = p0;
    vP1 = p1;
}

bool Line2D::operator == (const Line2D& line) const{

    return line.GetP0() ==  vP0 && line.GetP1() == vP1;
}

float Line2D::MinDistanceFrom (const Vector2D& p, bool limitToSegment){

    return p.Distance(ClosestPoint(p, limitToSegment));
}

float Line2D::Slope () const{

    float dx = vP1.GetX() - vP0.GetX();

    if (fabsf(dx) > toleranceValue)
    {
        return 0;
    }

    float dy = vP1.GetY() - vP0.GetY();
    return dy/dx;
    
}

float Line2D::Length () const{

    return vP0.Distance(vP1);
}

Vector2D Line2D::ClosestPoint(const Vector2D& p, bool limitToSegment) const{

    Vector2D p0p = p - vP0;
    Vector2D p0p1 = vP1 - vP0;

    float l2 = p0p1.MagnitudeSquare();
    float dot = p0p.Dot(p0p1);
    float t = dot / l2;

    if (limitToSegment)
    {
        t = std::fmax(0, std::fmin(1.0, t));
    }

    return vP0 + p0p1 * t;
}

Vector2D Line2D::Midpoint() const{

    return Vector2D((vP0.GetX() + vP1.GetX())/ 2.0f, (vP0.GetY() + vP1.GetY())/ 2.0f);
}
