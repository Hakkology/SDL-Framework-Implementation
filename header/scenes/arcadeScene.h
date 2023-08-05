#ifndef SCENES_ARCADESCENE_H
#define SCENES_ARCADESCENE_H

#include <memory>
#include <iostream>

#include "buttonoptionsScene.h"
#include "screen.h"
#include "color.h"
#include "gamecontroller.h"

enum eGame{
    TETRIS = 0,
    BREAK_OUT,
    ASTEROIDS,
    PACMAN,
    NUM_GAMES
};

class ArcadeScene : public ButtonOptionsScene {

public:

    ArcadeScene();
    virtual void Init () override;
    virtual void Update(uint32_t dt) override;
    virtual void Draw(Screen& theScreen) override;
    virtual const std::string& GetSceneName() const override;

private:

    std::unique_ptr<Scene> GetScene (eGame game);

    //temp

    // AnimatedSprite mSprite;
    // SpriteSheet mSpriteSheet;

};

#endif
