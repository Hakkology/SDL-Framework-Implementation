#ifndef UTILITIES_H
#define UTILITIES_H

#include <cmath>
#include <string>
#include <algorithm>
#include <cctype>

// variables
static const float toleranceValue = 0.0001f;

// functions
bool IsEqual(float x, float y);
bool IsGreaterThanOrEqual(float x, float y);
bool IsLessThanOrEqual(float x, float y);

float MillisecondstoSeconds (unsigned int milliseconds);
unsigned int GetIndex(unsigned int width, unsigned int r, unsigned int c);

bool StringCompare (const std::string& a, const std::string& b);

#endif