#ifndef GAMES_BREAKOUT_H
#define GAMES_BREAKOUT_H

#include <string>
#include <stdint.h>
#include <iostream>

#include "constants.h"
#include "game.h"
#include "app.h"
#include "gamecontroller.h"
#include "paddle.h"
#include "ball.h"
#include "levelboundary.h"
#include "bgamelevel.h"

enum BreakOutGameStates{

    IN_PLAY = 0,
    IN_SERVE,
    IN_GAME_OVER
};

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
    BGameLevel& GetCurrentLevel() {return bLevels[bCurrentLevel];}

    void SetToServeState();

    const Vector2D bBallVelocity = initBallVelocity;
    Paddle bPaddle;
    Ball bBall;
    LevelBoundary bLevelBoundary;
    BGameLevel bLevel;

    std::vector<BGameLevel> bLevels;
    size_t bCurrentLevel;
    BreakOutGameStates bGameState;

};

#endif