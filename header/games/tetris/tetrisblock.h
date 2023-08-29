#ifndef GAMES_TETRIS_TETRISBLOCK__H__
#define GAMES_TETRIS_TETRISBLOCK__H__

#include <map>
#include <vector>

#include "constants.h"
#include "inputaction.h"

class Screen;

class TetrisBlock{

public:

    virtual ~TetrisBlock();
    virtual void Init(Vector2D location);
    virtual void Update(uint32_t dt) = 0;
    virtual void Draw(Screen& screen) = 0;

    enum class RotationState { UP, RIGHT, DOWN, LEFT, NONE };

    virtual RotationState GetRotationState() const = 0;
    virtual void SetRotationState(RotationState state);
    void setShapeForRotation(RotationState state, const int shape[tBLockSize][tBLockSize]);
    const int (&getShapeForRotation(RotationState state))[tBLockSize][tBLockSize];

    void ResetShape();
    
    void rotateCW();
    void rotateCCW();

    void calculateDistance();
    void dropBlock();



protected:

    int shape[tBLockSize][tBLockSize];
    Vector2D tBlockPosition;
    std::map<RotationState, int[tBLockSize][tBLockSize]> tShapesByRotation;
    
};

#endif  //!GAMES_TETRIS_TETRISBLOCK__H__
