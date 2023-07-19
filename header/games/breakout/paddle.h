#ifndef GAMES_PADDLE_H
#define GAMES_PADDLE_H

#include <string>
#include <stdint.h>
#include <iostream>

#include "excluder.h"
#include "stdint.h"
#include "screen.h"

class Screen;

enum PaddleDirection{
    LEFT = 1 << 0,
    RIGHT = 1 << 1
};

class Paddle : public Excluder{

public:

    void Init (const Rectangle& rect, const Rectangle& boundary);
    void Update (uint32_t dt);
    void Draw (Screen& screen);

    inline bool IsMovingLeft() const {return bPaddleDirection == PaddleDirection::LEFT;}
    inline bool IsMovingRight() const {return bPaddleDirection == PaddleDirection::RIGHT;}
    inline void StopMovement() {bPaddleDirection = 0;}

    inline void SetMovementDirection (PaddleDirection dir) {bPaddleDirection |= dir;}
    inline void UnsetMovementDirection (PaddleDirection dir) {bPaddleDirection &= ~dir;}


private:

    uint32_t bPaddleDirection;
    Rectangle bBoundary;

};

#endif