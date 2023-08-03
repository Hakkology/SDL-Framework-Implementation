#ifndef APP_APP_H
#define APP_APP_H

#include <stdint.h>
#include <vector>
#include <memory>

#include "screen.h"
#include "scene.h"
#include "inputcontroller.h"
#include "bmpfont.h"

#include "arcadeScene.h"

struct SDL_Window;

class App{

public:
    static App& Singleton();
    bool Init (uint32_t width, uint32_t height, uint32_t mag);
    void Run();

    inline uint32_t Width() const {return aScreen.Width();}
    inline uint32_t Height() const {return aScreen.Height();}

    // Scene controllers
    void PushScene(std::unique_ptr<Scene> scene);
    void PopScene();
    Scene* TopScene(); // current scene

    static const std::string& GetBasePath();
    inline const BmpFont& GetFont() const {return bFont;}

private:
    Screen aScreen;
    SDL_Window* anoptrWindow;

    std::vector<std::unique_ptr<Scene>> aSceneStack;
    InputController aInputController;

    BmpFont bFont;
};

#endif
