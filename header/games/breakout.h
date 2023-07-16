#ifndef GAMES_BREAKOUT_H
#define GAMES_BREAKOUT_H

#include <string>
#include <stdint.h>
#include <iostream>

#include "game.h"

class GameController;
class Screen;

class BreakOut : public Game{

public:

    virtual ~BreakOut() {};
    virtual void Init(GameController& controller) override;
    virtual void Update(uint32_t dt) override;
    virtual void Draw (Screen& screen) override;
    virtual std::string GetName() const override;

};

#endif