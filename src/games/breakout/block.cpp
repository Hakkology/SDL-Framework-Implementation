#include "block.h"

Block::Block(): bOutlineColor(White()), bFillColor(White()), bHp(1){


}

void Block::Init(const Rectangle &rect, int hp, const Color &outlineColor, const Color &fillColor)
{

    Excluder::Init(rect);
    bHp = hp;
    bOutlineColor = outlineColor;
    bFillColor = fillColor;
}

void Block::Draw(Screen &screen){

    screen.Draw(GetRectangle(), bOutlineColor, true, bFillColor);
}

void Block::Bounce(Ball &ball, const BoundaryEdge& edge){

    ball.Bounce(edge);
}

void Block::ReduceHP(){

    if (bHp > 0)
    {
        --bHp;
    }
    
}
