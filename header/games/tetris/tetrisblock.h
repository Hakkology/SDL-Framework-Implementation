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

    enum class RotationState { UP, RIGHT, DOWN, LEFT, NUM_STATES };

    inline virtual RotationState GetRotationState() const {return tCurrentRotation;}
    inline void SetRotationState(RotationState state) {tCurrentRotation = state;}

    void SetShapeForRotation(RotationState state, const int inputShape[tBLockSize][tBLockSize]);
    const int (&GetShapeForRotation(RotationState state) const)[tBLockSize][tBLockSize] {return tShapesByRotation.at(state);}

    void ResetShape();
    
    void rotateCW();
    void rotateCCW();

    void calculateDistance();
    void dropBlock();

protected:

    int shape[tBLockSize][tBLockSize];
    std::map<RotationState, int[tBLockSize][tBLockSize]> tShapesByRotation;
    
    Vector2D tBlockPosition;
    RotationState tCurrentRotation = RotationState::UP;
    
};

#endif  //!GAMES_TETRIS_TETRISBLOCK__H__
