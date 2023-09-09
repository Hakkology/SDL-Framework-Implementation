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

    virtual int GetRotationState() const = 0;
    void SetRotationState(int state) {tCurrentState = state;}
    virtual int getNumStates() const = 0;

    void ResetShape();
    
    void rotateCW();
    void rotateCCW();

    void calculateDistance();
    void dropBlock();

protected:
    
    Vector2D tBlockPosition;
    int tCurrentState = 0;
    int tNumStates = 0;
    
};

#endif  //!GAMES_TETRIS_TETRISBLOCK__H__
