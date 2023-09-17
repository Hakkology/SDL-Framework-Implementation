#include <vector>
#include <memory>

#include "tetrisstartScene.h"
#include "app.h"
#include "notimplementedScene.h"
#include "gameScene.h"
#include "tetris.h"

TetrisStartScene::TetrisStartScene(): ButtonOptionsScene({"Play Game", "High Scores"}, Orange()){

}

void TetrisStartScene::Init(){

    ButtonAction backAction;
    backAction.key = GameController::CancelKey();
    backAction.action = [](uint32_t dt, InputState state){

        if (GameController::IsPressed(state))
        {
            App::Singleton().PopScene();
        }
    };
    sGameController.AddInputActionForKey(backAction);

    std::vector<Button::ButtonAction> actions;
    actions.push_back([this](){

        auto tetrisGame = std::make_unique<Tetris>();
        App::Singleton().PushScene(std::make_unique<GameScene>(std::move(tetrisGame)));

        //App::Singleton().PushScene(std::make_unique<NotImplementedScene>());

    });

    actions.push_back([this](){

        App::Singleton().PushScene(std::make_unique<NotImplementedScene>());
    });

    SetButtonActions(actions);
    ButtonOptionsScene::Init();
}

void TetrisStartScene::Update(uint32_t dt){

}

void TetrisStartScene::Draw(Screen &theScreen){

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

const std::string &TetrisStartScene::GetSceneName() const
{
    static std::string name = "Tetrus Start!";
    return name;
}
