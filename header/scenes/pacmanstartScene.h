#ifndef GAMES_PACMAN_PACMANSTARTSCENE__H__
#define GAMES_PACMAN_PACMANSTARTSCENE__H__

#include "buttonoptionsScene.h"

class PacmanStartScene : public ButtonOptionsScene
{

public:

    PacmanStartScene();
    virtual void Init () override;
    virtual void Update(uint32_t dt) override;
    virtual void Draw(Screen& theScreen) override;
    virtual const std::string& GetSceneName() const override;

private:
    /* data */
};



#endif  //!GAMES_PACMAN_PACMANSTARTSCENE__H__