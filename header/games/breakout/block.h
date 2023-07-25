#ifndef GAMES_BLOCK_H
#define GAMES_BLOCK_H

#include "excluder.h"
#include "color.h"
#include "block.h"
#include "screen.h"
#include "ball.h"

class Ball;
class Screen;
struct BoundaryEdge;

class Block : public Excluder{

public:

    static const int UNBREAKABLE = -1;

    Block();

    void Init (const Rectangle& rect, int hp, const Color& outlineColor, const Color& fillColor);
    void Draw (Screen& screen);
    void Bounce (Ball& ball, const BoundaryEdge& edge);

    void ReduceHP();

    inline int GetHP() const {return bHp;}
    inline bool IsDestroyed() const {return bHp == 0;}
    inline Color GetOutlineColor() const {return bOutlineColor;}
    inline Color GetFillColor() const {return bFillColor;}

private:
    Color bOutlineColor;
    Color bFillColor;

    int bHp; // -1 is unbreakable

};

#endif