#include "utilities.h"


bool IsEqual(float x, float y){

    return fabsf(x-y) < toleranceValue;
}

bool IsGreaterThanOrEqual(float x, float y){

    return x > y || IsEqual(x, y);
}

bool IsLessThanOrEqual(float x, float y){

    return x < y || IsEqual(x, y);
}