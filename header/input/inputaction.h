#ifndef INPUT_INPUTACTION_H
#define INPUT_INPUTACTION_H

#include <functional>
#include <stdint.h>
#include <vector>

using InputKey = uint8_t;
using InputState = uint8_t;

using InputAction = std::function<void(uint32_t dt, InputState)>;

struct ButtonAction{

    InputKey key;
    InputAction action;
};




#endif