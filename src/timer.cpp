#include "timer.h"

void Timer::Start()
{
    tStartTicks = SDL_GetTicks();
}

void Timer::End()
{
    tEndTicks = SDL_GetTicks();
}

float Timer::DeltaTime() const
{
    return (tEndTicks - tStartTicks) / 1000.0f;
}
