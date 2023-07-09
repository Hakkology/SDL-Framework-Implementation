#ifndef SHAPES_SHAPE_H
#define SHAPES_SHAPE_H

#include <vector>

#include "vector2D.h"

class Shape{

public:

    virtual Vector2D GetCenterPoint() const = 0;
    inline virtual std::vector<Vector2D> GetPoints() const {return sPoints;}

    void MoveBy(const Vector2D& deltaOffset);


    virtual ~Shape() {}

protected:

    std::vector<Vector2D> sPoints;
};



#endif