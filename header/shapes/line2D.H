#ifndef SHAPES_LINE2D_H
#define SHAPES_LINE2D_H

#include <stdint.h>
#include <cmath>

#include <SDL2/SDL.h>

#include "vector2D.h"
#include "utilities.h"

class Line2D{


public:

    Line2D();
    Line2D(float x0, float y0, float x1, float y1);
    Line2D(const Vector2D& p0, const Vector2D& p1);

    inline const Vector2D& GetP0() const {return vP0;}
    inline const Vector2D& GetP1() const {return vP1;}

    inline void SetP0(const Vector2D& p0) {vP0 = p0;}
    inline void SetP1(const Vector2D& p1) {vP1 = p1;}

    bool operator == (const Line2D& line) const;

    float MinDistanceFrom (const Vector2D& p, bool limitToSegment = false);
    float Slope () const;
    float Length () const;

    Vector2D ClosestPoint(const Vector2D& p, bool limitToSegment) const;
    Vector2D Midpoint() const;

private:

    Vector2D vP0;
    Vector2D vP1;

};

#endif