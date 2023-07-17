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
    NONE = 0,
    LEFT,
    RIGHT
};

class Paddle : public Excluder{

public:

    void Init (const Rectangle& rect);
    void Update (uint32_t dt);
    void Draw (Screen& screen);

    inline bool IsMovingLeft() const {return bPaddleDirection == PaddleDirection::LEFT;}
    inline bool IsMovingRight() const {return bPaddleDirection == PaddleDirection::RIGHT;}
    inline void StopMovement() {bPaddleDirection = PaddleDirection::NONE;}
    inline void SetMovementDirection (PaddleDirection dir) {bPaddleDirection == dir;}


private:

    PaddleDirection bPaddleDirection;

};

#endif