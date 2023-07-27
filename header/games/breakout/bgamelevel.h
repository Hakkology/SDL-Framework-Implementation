#ifndef GAMES_BGAMELEVEL_H
#define GAMES_BGAMELEVEL_H

#include <vector>
#include <stdint.h>

#include "block.h"
#include "ball.h"
#include "filecommandloader.h"

class Screen;
class Rectangle;

struct LayoutBlock{

    char symbol = '-';
    int hp = 0;
    Color color = Black();
};

class BGameLevel{

public:

    BGameLevel();

    void Init (const Rectangle& boundary);
    void Load(const std::vector<Block>& blocks);
    void Update (uint32_t dt, Ball& ball);
    void Draw (Screen& screen);

    static std::vector<BGameLevel> LoadLevelsFromFile(const std::string& filePath);
    static LayoutBlock FindLayoutBlockForSymbol(const std::vector<LayoutBlock>& blocks, char symbol);

    bool IsLevelComplete() const;

private:
    
    void CreateDefaultLevel (const Rectangle& rect);

    std::vector<Block> bBlocks;
};

#endif // DEBUG
