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
                edgeToBounceOffOf = edge;
                noptrBlockToBounceOffOf = &block;
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
