#ifndef SCENES_ASTEROIDSTARTSCENE__H__
#define SCENES_ASTEROIDSTARTSCENE__H__

#include "buttonoptionsScene.h"

class AsteroidStartScene : public ButtonOptionsScene
{

public:

    AsteroidStartScene();
    virtual void Init () override;
    virtual void Update(uint32_t dt) override;
    virtual void Draw(Screen& theScreen) override;
    virtual const std::string& GetSceneName() const override;

private:
    /* data */
};


#endif  //!SCENES_ASTEROIDSSTARTSCENE__H__