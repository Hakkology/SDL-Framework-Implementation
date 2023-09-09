#include "tetrisblock.h"

class TBlock :  public TetrisBlock
{

public:
    void Init(Vector2D location) override;
    void Update(uint32_t dt) override;
    void Draw(Screen& screen) override;

    enum RotationState { UP, RIGHT, DOWN, LEFT, NUM_STATES };

    inline int getNumStates() const override {return static_cast<int>(RotationState::NUM_STATES);}
    int GetRotationState() const override {return tCurrentState;}
    void SetRotationState(int state) {tCurrentState = intToRotationState(state);}

    RotationState intToRotationState(int state) const;


private:

    std::map<RotationState, int[tBLockSize][tBLockSize]> tShapesByRotation;
    
};


