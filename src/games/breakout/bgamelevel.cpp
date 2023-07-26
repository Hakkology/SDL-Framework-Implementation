#include "bgamelevel.h"

BGameLevel::BGameLevel(){
    
}

void BGameLevel::Init(const Rectangle &boundary){

    CreateDefaultLevel(boundary);
}

void BGameLevel::Load(const std::vector<Block> &blocks){

    bBlocks.clear();
    bBlocks = blocks;
}

void BGameLevel::Update(uint32_t dt, Ball &ball){

    std::vector<Block> collidedBlocks;

    BoundaryEdge edgeToBounceOffOf;
    Block* noptrBlockToBounceOffOf = nullptr;

    float largestMagnitude = -1.0f;

    for(auto& block: bBlocks){

        BoundaryEdge edge;
        if (!block.IsDestroyed() && block.HasCollided(ball.GetBoundingRect(), edge))
        {
            collidedBlocks.push_back(block);
            float magnitude = block.GetCollisionOffset(ball.GetBoundingRect()).Magnitude();

            if (magnitude > largestMagnitude)
            {
                largestMagnitude = magnitude;
                edgeToBounceOffOf = edge;
                noptrBlockToBounceOffOf = &block;
            }
        }
    }

    if (noptrBlockToBounceOffOf != nullptr)
    {
        noptrBlockToBounceOffOf->Bounce(ball, edgeToBounceOffOf);
        noptrBlockToBounceOffOf->ReduceHP();
    }

    for(const auto & block : collidedBlocks){

        BoundaryEdge edge;
        if (block.HasCollided(ball.GetBoundingRect(), edge))
        {
            Vector2D p;
            ball.MakeFlushWithEdge(edge, p , true);
        }
        
    }
}

void BGameLevel::Draw(Screen &screen){

    for(auto& block: bBlocks){

        if (!block.IsDestroyed())
        {
            block.Draw(screen);
        }
        
    }
}

void BGameLevel::CreateDefaultLevel(const Rectangle &rect){

    bBlocks.clear();

    const int NUM_BLOCKS_ACROSS = ((int) rect.GetWidth() - (2*(BLOCK_WIDTH)) / BLOCK_WIDTH);
    const int NUM_BLOCKS_ROWS = 5;

    float startX = ((int)rect.GetWidth() - (NUM_BLOCKS_ACROSS * (BLOCK_WIDTH+1)))/2;

    Color colors [NUM_BLOCKS_ROWS];
    colors [0] = Yellow();
    colors [1] = Magenta();
    colors [2] = Pink();
    colors [3] = Green();
    colors [4] = Cyan();

    for (int r = 0; r < NUM_BLOCKS_ROWS; r++)
    {
        Rectangle blockRect = {Vector2D(startX, BLOCK_HEIGHT * (r+1)), BLOCK_WIDTH, BLOCK_HEIGHT};

        for (int c = 0; c < NUM_BLOCKS_ACROSS; ++c)
        {
            Block b;
            b.Init(blockRect, 1, Black(), colors[r]);
            bBlocks.push_back(b);
            blockRect.MoveBy(Vector2D(BLOCK_WIDTH, 0));
        }   
    }
}

LayoutBlock BGameLevel::FindLayoutBlockForSymbol(const std::vector<LayoutBlock> &blocks, char symbol)
{
    for (int i = 0; i < blocks.size(); ++i)
    {
        if (blocks[i].symbol == symbol)
        {
            return blocks[i];
        }
    }

    return LayoutBlock();
}

std::vector<BGameLevel> BGameLevel::LoadLevelsFromFile(const std::string &filePath)
{
    std::vector<BGameLevel> levels;
    std::vector<LayoutBlock> layoutBlocks;
    std::vector<Block> levelBlocks;

    int width = 0;
    int height = 0;

    FileCommandLoader fileLoader;

    Command levelCommand;
    levelCommand.command = "level";
    levelCommand.parseFunc = [&](ParseFuncParams params){

        if (levels.size() > 0)
        {
            levels.back().Load(levelBlocks);
        }
        layoutBlocks.clear();
        levelBlocks.clear();
        width = 0;
        height = 0;

        BGameLevel level;
        level.Init(Rectangle(Vector2D::Zero, SCREEN_WIDTH, SCREEN_HEIGHT));

        levels.push_back(level);
    };

    fileLoader.AddCommand(levelCommand);

    Command blockCommand;
    blockCommand.command = "block";
    blockCommand.parseFunc = [&] (ParseFuncParams params){

        LayoutBlock lb;

        layoutBlocks.push_back(lb);
    };

    fileLoader.AddCommand(blockCommand);

    Command symbolCommand;
    symbolCommand.command = "symbol";
    symbolCommand.parseFunc = [&](ParseFuncParams params){

        layoutBlocks.back().symbol = FileCommandLoader::ReadChar(params);
    };

    fileLoader.AddCommand(symbolCommand);

    Command fillColorCommand;
    fillColorCommand.command = "fillcolor";
    fillColorCommand.parseFunc = [&](ParseFuncParams params){

        layoutBlocks.back().color = FileCommandLoader::ReadColor(params);
    };

    fileLoader.AddCommand(fillColorCommand);

    Command hpCommand;
    hpCommand.command = "hp";
    hpCommand.parseFunc = [&](ParseFuncParams params){

        layoutBlocks.back().hp = FileCommandLoader::ReadInt(params);
    };

    fileLoader.AddCommand(hpCommand);

    Command widthCommand;
    widthCommand.command = "width";
    widthCommand.parseFunc = [&](ParseFuncParams params){

        width = FileCommandLoader::ReadInt(params);
    };

    fileLoader.AddCommand(widthCommand);

    Command heightCommand;
    heightCommand.command = "height";
    heightCommand.parseFunc = [&](ParseFuncParams params){

        height = FileCommandLoader::ReadInt(params);
    };

    fileLoader.AddCommand(heightCommand);

    Command layoutCommand;
    layoutCommand.commandType = COMMAND_MULTI_LINE;
    layoutCommand.command = "layout";
    layoutCommand.parseFunc = [&](ParseFuncParams params){

        int blockWidth = BLOCK_WIDTH;
        int blockHeight = BLOCK_HEIGHT;

        float startingX = 0; //static_cast<float>(screenWidth - blockWidth*width) /2.0f;
        Rectangle blockRect (Vector2D(startingX, (params.lineNum+1) * blockHeight), blockWidth, blockHeight);

        for (int c = 0; c < params.line.length(); ++c)
        {
            if (params.line[c] != '-')
            {
                LayoutBlock layoutBlock = FindLayoutBlockForSymbol(layoutBlocks, params.line[c]);

                Block b;
                b.Init(blockRect, layoutBlock.hp, Black(), layoutBlock.color);
                levelBlocks.push_back(b);
            }
            blockRect.MoveBy(Vector2D(blockWidth, 0));
        }
    };

    fileLoader.AddCommand(layoutCommand);
    fileLoader.LoadFile(filePath);

    if (levels.size() > 0)
    {
        levels.back().Load(levelBlocks);
    }
    
    return levels;
}
