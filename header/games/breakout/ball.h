#ifndef GAMES_BALL_H
#define GAMES_BALL_H

#include <stdint.h>

#include "rectangle.h"
#include "utilities.h"
#include "screen.h"
#include "circle.h"
#include "boundaryedge.h"

class Screen;
struct BoundaryEdge;

class Ball{

public:

    Ball();
    Ball(const Vector2D& pos, float radius);

    void Update(uint32_t dt);
    void Draw(Screen& screen);

    void Bounce(const BoundaryEdge& edge);

    void MakeFlushWithEdge (const BoundaryEdge& edge, Vector2D& pointOnEdge, bool limitToEdge);
    void MoveTo (const Vector2D& point);

    inline const Rectangle GetBoundingRect() const {return bBoundingBox;};
    inline void Stop() {bVelocity = Vector2D::Zero;}
    inline void SetVelocity(const Vector2D& vel) {bVelocity=vel;}
    inline float GetRadius() const {return bBoundingBox.GetWidth()/2.0f;}
    inline Vector2D GetPosition() const {return bBoundingBox.GetCenterPoint();}

private:

    Rectangle bBoundingBox;
    Vector2D bVelocity;
};

#endif