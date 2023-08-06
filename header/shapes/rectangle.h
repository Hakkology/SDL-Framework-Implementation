#ifndef SHAPES_RECTANGLE_H
#define SHAPES_RECTANGLE_H

#include <cmath>

#include "utilities.h"
#include "shape.h"


class Rectangle : public Shape{

public:

    Rectangle();
    Rectangle(const Vector2D& topLeft, unsigned int width, unsigned int height);
    Rectangle(const Vector2D topLeft, const Vector2D bottomRight);

    inline void SetTopLeftPoint (const Vector2D& topLeft) {sPoints[0] = topLeft;}
    inline void SetBottomRightPoint (const Vector2D& bottomRight) {sPoints[1] = bottomRight;}

    inline Vector2D GetTopLeftPoint() const {return sPoints[0];}
    inline Vector2D GetBottomRightPoint() const {return sPoints[1];}

    float GetWidth() const;
    float GetHeight() const;

    void MoveTo(const Vector2D& position);

    virtual Vector2D GetCenterPoint() const override;

    bool Intersects(const Rectangle& otherRectangle) const;
    bool ContainsPoint(const Vector2D& point) const;

    static Rectangle Inset (const Rectangle& rect, const Vector2D& insets);

    virtual std::vector<Vector2D> GetPoints() const override;

};

#endif