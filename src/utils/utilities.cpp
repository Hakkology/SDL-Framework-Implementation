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

float MillisecondstoSeconds(unsigned int milliseconds)
{
    return static_cast<float>(milliseconds) / 1000.0f;
}
