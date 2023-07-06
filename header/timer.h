#ifndef TIMER_H
#define TIMER_H

#include <stdint.h>

#include <SDL2/SDL.h>

class Timer{

public:

    Timer(){
        
        tStartTicks = 0;
        tEndTicks = 0;
    }

    void Start();
    void End();
    float DeltaTime() const;

private:

    uint32_t tStartTicks;
    uint32_t tEndTicks;
};

 #endif