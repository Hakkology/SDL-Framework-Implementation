#ifndef GAMES_BREAKOUT_H
#define GAMES_BREAKOUT_H

#include <string>
#include <stdint.h>
#include <iostream>

#include "constants.h"
#include "game.h"
#include "circle.h"
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

    void ResetGame(size_t toLevel = 2);
    void SetToServeState();
    void ReduceLifeByOne();

    BGameLevel& GetCurrentLevel() {return bLevels[bCurrentLevel];}
    bool IsBallPassedCutoffY() const;
    bool IsGameOver() const {return bLives < 0;}

    const Vector2D bBallVelocity = initBallVelocity;
    Paddle bPaddle;
    Ball bBall;
    LevelBoundary bLevelBoundary;
    BGameLevel bLevel;

    std::vector<BGameLevel> bLevels;
    size_t bCurrentLevel;
    BreakOutGameStates bGameState;

    int bLives;
    float bCutoff;
};

#endif