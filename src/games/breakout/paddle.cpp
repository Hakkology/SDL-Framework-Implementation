#include "paddle.h"

void Paddle::Init(const Rectangle &rect){

    Excluder::Init(rect);
    bPaddleDirection = PaddleDirection::NONE;
}

void Paddle::Update(uint32_t dt){
     
     if (bPaddleDirection != PaddleDirection::NONE)
     {
        Vector2D direction;
        if (bPaddleDirection == PaddleDirection::LEFT){
            direction = LEFT_DIR;
        }
        else{
            direction = RIGHT_DIR;
        }
        
        Vector2D dx = direction * paddleVelocity * MillisecondstoSeconds(dt);

        MoveBy(dx);
     } 
}

void Paddle::Draw(Screen &screen){

    screen.Draw(GetRectangle(), Blue(), true, Blue());
}