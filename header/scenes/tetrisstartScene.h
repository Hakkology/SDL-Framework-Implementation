#ifndef SCENES_TETRIMONIUMSTARTSCENE__H__
#define SCENES_TETRIMONIUMSTARTSCENE__H__

#include "buttonoptionsScene.h"

class TetrisStartScene : public ButtonOptionsScene
{

public:

    TetrisStartScene();
    virtual void Init () override;
    virtual void Update(uint32_t dt) override;
    virtual void Draw(Screen& theScreen) override;
    virtual const std::string& GetSceneName() const override;

private:
    /* data */
};


#endif  //!SCENES_TETRIMONIUMSTARTSCENE__H__