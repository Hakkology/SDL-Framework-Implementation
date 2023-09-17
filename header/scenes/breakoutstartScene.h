#ifndef SCENES_BREAKOUTSTARTSCENE__H__
#define SCENES_BREAKOUTSTARTSCENE__H__

#include "buttonoptionsScene.h"

class BreakoutStartScene : public ButtonOptionsScene
{

public:

    BreakoutStartScene();
    virtual void Init () override;
    virtual void Update(uint32_t dt) override;
    virtual void Draw(Screen& theScreen) override;
    virtual const std::string& GetSceneName() const override;

private:
    /* data */
};


#endif  //!SCENES_BREAKOUTSTARTSCENE__H__