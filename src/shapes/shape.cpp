#include "shape.h"

void Shape::MoveBy(const Vector2D &deltaOffset){

    for(Vector2D& point : sPoints) {

        point = point + deltaOffset;
    }
}
