#include "vector2D.h"
#include "utilities.h"

const Vector2D Vector2D::Zero;

#pragma region Operators 

std::ostream& operator << (std::ostream& consoleOut, const Vector2D vec2D){

    std::cout << "X: " << vec2D.vx << " ,Y: " << vec2D.vy << std::endl;
    return consoleOut;
}

bool Vector2D::operator == (const Vector2D vec2) const{

    return IsEqual(vx, vec2.vx) && IsEqual(vy, vec2.vy);
}

bool Vector2D::operator != (const Vector2D vec2) const{

    return !(*this == vec2);
}

Vector2D Vector2D::operator-() const{

    return Vector2D (-vx, -vy);
}

Vector2D Vector2D::operator*(float scalar) const{

    return Vector2D (vx * scalar, vy * scalar);
}

Vector2D operator*=(float scalar, const Vector2D& vec2D){

    return vec2D * scalar;
}

Vector2D Vector2D::operator*=(float scalar){

    *this = *this * scalar;
    return *this;
}

Vector2D Vector2D::operator/(float scalar) const{

    assert(fabsf(scalar) > toleranceValue);
    return Vector2D (vx / scalar, vy / scalar);
}

Vector2D operator/=(float scalar, const Vector2D& vec2D){

    assert(fabsf(scalar) > toleranceValue);
    return vec2D / scalar;
}

Vector2D Vector2D::operator/=(float scalar){

    assert(fabsf(scalar) > toleranceValue);
    *this = *this / scalar;
    return *this;
}

Vector2D Vector2D::operator+(const Vector2D& vec2D) const{

    return Vector2D ((vx + vec2D.vx), (vy + vec2D.vy));
}

Vector2D Vector2D::operator+=(const Vector2D& vec2D){

    *this = *this + vec2D;
    return *this;
}

Vector2D Vector2D::operator-(const Vector2D& vec2D) const{

    return Vector2D ((vx - vec2D.vx), (vy - vec2D.vy));
}

Vector2D Vector2D::operator-=(const Vector2D& vec2D){

    *this = *this - vec2D;
    return *this;
}

#pragma endregion

float Vector2D::Magnitude() const{

    return sqrt(MagnitudeSquare());
}

Vector2D Vector2D::GetUnitVector() const{

    float mag = Magnitude();

    if (mag > toleranceValue)
    {
        return *this / mag;
    }
    return Vector2D::Zero;
}

Vector2D Vector2D::Normalize(){

    float mag = Magnitude();

    if (mag > toleranceValue)
    {
        *this /= mag;
    }
    return *this;
}

float Vector2D::Distance(const Vector2D& vec2D) const{

    return (vec2D - *this).Magnitude();
}

float Vector2D::Dot(const Vector2D& vec2D) const{

    return vx * vec2D.vx + vy * vec2D.vy;
}

Vector2D Vector2D::ProjectOnto(const Vector2D& vec2D) const{

    Vector2D UnitVec2D = vec2D.GetUnitVector();
    float dot = Dot(UnitVec2D);
    return UnitVec2D * dot;

}

float Vector2D::AngleBetween(const Vector2D& vec2D) const{

    return acosf(GetUnitVector().Dot(vec2D.GetUnitVector()));
}

Vector2D Vector2D::Reflect(const Vector2D& normal) const{

    return *this - (ProjectOnto(normal) * 2);
}

Vector2D Vector2D::RotationResult(float angle, const Vector2D aroundPoint) const{

    float sin = sinf(angle);
    float cos = cosf(angle);

    Vector2D thisVec2D(vx, vy);

    thisVec2D -= aroundPoint;

    float xRot = thisVec2D.vx * cos - thisVec2D.vy * sin;
    float yRot = thisVec2D.vx * sin + thisVec2D.vy * cos;

    Vector2D rotatedVector(xRot, yRot);

    return rotatedVector + aroundPoint;
}

void Vector2D::Rotate(float angle, const Vector2D aroundPoint){

    float sin = sinf(angle);
    float cos = cosf(angle);

    Vector2D thisVec2D(vx, vy);

    thisVec2D -= aroundPoint;

    float xRot = thisVec2D.vx * cos - thisVec2D.vy * sin;
    float yRot = thisVec2D.vx * sin + thisVec2D.vy * cos;

    Vector2D rotatedVector(xRot, yRot);

    *this = rotatedVector + aroundPoint;
}

float Vector2D::MagnitudeSquare() const{

    return Dot(*this);
}