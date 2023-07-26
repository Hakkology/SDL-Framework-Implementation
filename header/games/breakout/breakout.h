#ifndef GAMES_BREAKOUT_H
#define GAMES_BREAKOUT_H

#include <string>
#include <stdint.h>
#include <iostream>

#include "game.h"
#include "app.h"
#include "gamecontroller.h"
#include "paddle.h"
#include "ball.h"
#include "levelboundary.h"
#include "bgamelevel.h"

class GameController;
class Screen;

class BreakOut : public Game{

public:

    //virtual ~BreakOut() {};
    virtual void Init(GameController& controller) override;
    virtual void Update(uint32_t dt) override;
    virtual void Draw (Screen& screen) override;
    virtual const std::string& GetName() const override;

private:

    void ResetGame();

    Paddle bPaddle;
    Ball bBall;
    const Vector2D bBallVelocity = initBallVelocity;
    LevelBoundary bLevelBoundary;
    BGameLevel bLevel;

};

#endif