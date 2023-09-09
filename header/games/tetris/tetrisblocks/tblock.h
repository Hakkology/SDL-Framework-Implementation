#include "tetrisblock.h"

class TBlock :  public TetrisBlock
{

public:
    void Init(Vector2D location);
    void Update(uint32_t dt);
    void Draw(Screen& screen);

    enum class RotationState { UP, RIGHT, DOWN, LEFT };
private:
    
};


