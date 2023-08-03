#ifndef SCENES_NOTIMPLEMENTEDSCENE__H__
#define SCENES_NOTIMPLEMENTEDSCENE__H__

#include "scene.h"

class Screen;

class NotImplementedScene: public Scene{

public:

    virtual void Init() override;
    virtual void Update (uint32_t dt) override;
    virtual void Draw (Screen& screen) override;

    virtual const std::string& GetSceneName() const override;

private:

};

#endif  //!__NOTIMPLEMENTEDSCENE__H__