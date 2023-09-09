#include "tetrisblock.h"

void TetrisBlock::rotateCW(){
    int numStates = static_cast<int>(RotationState::NUM_STATES);
    int currentState = static_cast<int>(GetRotationState());
    int nextState = (currentState + 1) % numStates;
    SetRotationState(static_cast<RotationState>(nextState));
}

void TetrisBlock::rotateCCW(){
    int numStates = static_cast<int>(RotationState::NUM_STATES); 
    int currentState = static_cast<int>(GetRotationState());
    int nextState = (currentState - 1 + numStates) % numStates;
    SetRotationState(static_cast<RotationState>(nextState));
}

void TetrisBlock::SetShapeForRotation(RotationState state, const int inputShape[tBLockSize][tBLockSize]) {
    for (int i = 0; i < tBLockSize; ++i) {
        for (int j = 0; j < tBLockSize; ++j) {
            tShapesByRotation[state][i][j] = inputShape[i][j];
        }
    }
}

