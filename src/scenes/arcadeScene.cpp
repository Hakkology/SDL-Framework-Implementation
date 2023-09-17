#include "arcadeScene.h"
#include "app.h"

#include "gameScene.h"
#include "breakout.h"
#include "pacmanstartScene.h"
#include "tetrisstartScene.h"
#include "asteroidstartScene.h"
#include "notimplementedScene.h"

ArcadeScene::ArcadeScene():ButtonOptionsScene({"Tetris", "Break Out!", "Asteroids", "Pac-mania!"}, Magenta()){


}

void ArcadeScene::Init (){

    std::vector<Button::ButtonAction> actions;

    actions.push_back([this]{

        App::Singleton().PushScene(GetScene(TETRIS));
    });

    actions.push_back([this]{

        App::Singleton().PushScene(GetScene(BREAK_OUT));
    });

    actions.push_back([this]{

        App::Singleton().PushScene(GetScene(ASTEROIDS));
    });

    actions.push_back([this]{

        App::Singleton().PushScene(GetScene(PACMAN));
    });

    SetButtonActions(actions);
    ButtonOptionsScene::Init();

    //temp
    {

    }

}

void ArcadeScene::Update(uint32_t dt){

}

void ArcadeScene::Draw(Screen& theScreen){

    const BmpFont& font = App::Singleton().GetFont();

    Rectangle rect = {Vector2D::Zero, App::Singleton().Width(), App::Singleton().Height()/3};
    Vector2D textDrawPosition;
    textDrawPosition = font.GetDrawPosition("GAME STATION", rect, BFXA_CENTER, BFYA_CENTER);

    theScreen.Draw(font, "GAME STATION", textDrawPosition, Orange());

    Triangle triangle = {Vector2D (20, 30), Vector2D (10, 130), Vector2D (60,20)};
    theScreen.Draw (triangle, Lilac(), true, Lilac());
    Circle circle = {Vector2D(theScreen.Width()/2 +150, theScreen.Height()/2 -50), 60};
    theScreen.Draw (circle, Green(), true, Green());
    Rectangle rectangle = {Vector2D(theScreen.Width()/2-60, theScreen.Height()/2+75),120,45};
    theScreen.Draw (rectangle, Blue(), true, Blue());

    ButtonOptionsScene::Draw(theScreen);
    
}

const std::string& ArcadeScene::GetSceneName() const{

    static std::string sceneName = "Arcade";
    return sceneName;
}

std::unique_ptr<Scene> ArcadeScene::GetScene(eGame game){

    switch (game)
    {
        case TETRIS:
            return std::make_unique<TetrisStartScene>();
        break;
        
        case BREAK_OUT:
        {
            std::unique_ptr<BreakOut> breakoutGame = std::make_unique<BreakOut>();
            std::unique_ptr<GameScene> breakoutScene = std::make_unique<GameScene>(std::move(breakoutGame));
        return breakoutScene;
        }
        break;
        
        case ASTEROIDS:
            return std::make_unique<AsteroidStartScene>();
        break;

        case PACMAN:
            return std::make_unique<PacmanStartScene>();
        break;

    }

    std::unique_ptr<Scene> notImplementedScene = std::make_unique<NotImplementedScene>();
    return notImplementedScene;
}