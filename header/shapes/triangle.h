#ifndef SHAPES_TRIANGLE_H
#define SHAPES_TRIANGLE_H

#include <cmath>
#include "utilities.h"

#include "shape.h"


class Triangle: public Shape{

public:

    Triangle();
    Triangle(const Vector2D& p0, const Vector2D& p1, const Vector2D& p2);

    inline void SetP0 (const Vector2D& p0) {sPoints[0] = p0;}
    inline void SetP1 (const Vector2D& p1) {sPoints[1] = p1;}
    inline void SetP2 (const Vector2D& p2) {sPoints[2] = p2;}

    inline Vector2D GetP0() const {return sPoints[0];}
    inline Vector2D GetP1() const {return sPoints[1];}
    inline Vector2D GetP2() const {return sPoints[2];}

    virtual Vector2D GetCenterPoint() const override;

    float ContainsPoint(const Vector2D& p) const;

private:
    float Area() const;
    float Area(const Vector2D& p0, const Vector2D& p1, const Vector2D& p2) const;
};

#endif