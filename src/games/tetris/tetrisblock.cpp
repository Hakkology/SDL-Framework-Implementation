#include "tetrisblock.h"

void TetrisBlock::rotateCW() {
    int numStates = getNumStates();
    int currentState = GetRotationState();
    int nextState = (currentState + 1) % numStates;
    SetRotationState(nextState);
}

void TetrisBlock::rotateCCW() {
    int numStates = getNumStates();
    int currentState = GetRotationState();
    int nextState = (currentState - 1 + numStates) % numStates;
    SetRotationState(nextState);
}

