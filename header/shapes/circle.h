#ifndef SHAPES_CIRCLE_H
#define SHAPES_CIRCLE_H

#include <cmath>

#include "utilities.h"
#include "shape.h"


class Circle : public Shape{

public:

    Circle();
    Circle(const Vector2D& center, float radius);

    inline virtual Vector2D GetCenterPoint() const override {return sPoints[0];}
    inline float GetRadius() const {return cRadius;}
    inline void SetRadius (float radius) {cRadius = radius;}
    inline void MoveTo(const Vector2D& position) {sPoints[0] = position;}

    bool Intersects(const Circle& otherCircle);
    bool ContainsPoint(const Vector2D& point) const;

private:
    float cRadius;

};

#endif