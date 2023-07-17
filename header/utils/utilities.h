#ifndef UTILITIES_H
#define UTILITIES_H

#include <cmath>

// variables
static const float toleranceValue = 0.0001f;

// functions
bool IsEqual(float x, float y);
bool IsGreaterThanOrEqual(float x, float y);
bool IsLessThanOrEqual(float x, float y);
float MillisecondstoSeconds (unsigned int milliseconds);

#endif