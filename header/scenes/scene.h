#ifndef SCENES_SCENE_H
#define SCENES_SCENE_H

#include <stdint.h>
#include <string>

#include "gamecontroller.h"

class Screen;

class Scene{

public:

    virtual ~Scene() {}
    virtual void Init () = 0;
    virtual void Update(uint32_t dt) = 0;
    virtual void Draw(Screen& theScreen) =0;
    virtual const std::string& GetSceneName() const = 0;

    GameController* GetGameController() {return &sGameController;}

protected:
    GameController sGameController;

};

#endif
