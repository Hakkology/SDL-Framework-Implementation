#ifndef VECTOR2D_H
#define VECTOR2D_H

using namespace std;

#include <iostream>
#include <cassert>
#include <cmath>

class Vector2D{

public:

    Vector2D(): Vector2D(0, 0) {}
    Vector2D(float x, float y): vx(x), vy(y) {};

    static const Vector2D Zero;

    inline void SetX(float x) {vx = x;}
    inline void SetY(float y) {vy = y;}

    inline float GetX() const {return vx;}
    inline float GetY() const {return vy;}

    friend std::ostream& operator << (std::ostream& consoleOut, const Vector2D vec2D);

    // operators

    bool operator == (const Vector2D vec2) const;
    bool operator != (const Vector2D vec2) const;

    Vector2D operator-() const;
    Vector2D operator*(float scalar) const;
    Vector2D operator/(float scalar) const;
    Vector2D operator*=(float scalar);
    Vector2D operator/=(float scalar);
    friend Vector2D operator*=(float scalar, const Vector2D& vec2D);
    friend Vector2D operator/=(float scalar, const Vector2D& vec2D);

    Vector2D operator+(const Vector2D& vec2D) const;
    Vector2D operator-(const Vector2D& vec2D) const;
    Vector2D operator+=(const Vector2D& vec2D);
    Vector2D operator-=(const Vector2D& vec2D);

    float Magnitude() const;
    float MagnitudeSquare() const;

    Vector2D GetUnitVector() const;
    Vector2D Normalize();
    Vector2D ProjectOnto(const Vector2D& vec2D) const;
    Vector2D Reflect(const Vector2D& normal) const;
    Vector2D RotationResult(float angle, const Vector2D& aroundPoint) const;

    float Distance(const Vector2D& vec2D) const;
    float Dot(const Vector2D& vec2D) const;
    float AngleBetween(const Vector2D& vec2D) const;

    void Rotate(float angle, const Vector2D& aroundPoint);

private:

    float vx, vy;
};


#endif