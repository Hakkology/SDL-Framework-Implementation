#ifndef SCENES_GAMESCENE_H
#define SCENES_GAMESCENE_H

#include "scene.h"
#include "game.h"

#include <memory>

class Screen;

class Scene{

public:

    virtual ~Scene() {}
    virtual void Init () = 0;
    virtual void Update(uint32_t dt) = 0;
    virtual void Draw(Screen& theScreen) =0;
    virtual const std::string& GetSceneName() const = 0;



protected:


};

#endif
