#ifndef GAMES_BGAMELEVEL_H
#define GAMES_BGAMELEVEL_H

#include <vector>

#include "block.h"
#include "ball.h"

class Screen;
class Rectangle;

class BGameLevel{

public:

    BGameLevel();

    void Init (const Rectangle& boundary);
    void Load(const std::vector<Block>& blocks);
    void Update (uint32_t dt, Ball& ball);
    void Draw (Screen& screen);

private:
    
    void CreateDefaultLevel (const Rectangle& rect);
    std::vector<Block> bBlocks;
};

#endif // DEBUG
