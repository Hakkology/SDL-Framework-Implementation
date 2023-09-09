#include "tblock.h"

TBlock::RotationState intToRotationState(int state) {
    switch(state) {
        case 0: return TBlock::RotationState::UP;
        case 1: return TBlock::RotationState::RIGHT;
        case 2: return TBlock::RotationState::DOWN;
        case 3: return TBlock::RotationState::LEFT;
        default: throw std::runtime_error("Invalid state!");
    }
}
