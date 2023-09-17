#include <vector>
#include <memory>

#include "breakoutstartScene.h"
#include "app.h"
#include "notimplementedScene.h"
#include "gameScene.h"
#include "breakout.h"

BreakoutStartScene::BreakoutStartScene(): ButtonOptionsScene({"Play Game", "High Scores"}, Green()){

}

void BreakoutStartScene::Init(){

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

        auto breakoutgame = std::make_unique<BreakOut>();
        App::Singleton().PushScene(std::make_unique<GameScene>(std::move(breakoutgame)));

        // App::Singleton().PushScene(std::make_unique<NotImplementedScene>());

    });

    actions.push_back([this](){

        App::Singleton().PushScene(std::make_unique<NotImplementedScene>());
    });

    SetButtonActions(actions);
    ButtonOptionsScene::Init();
}

void BreakoutStartScene::Update(uint32_t dt){

}

void BreakoutStartScene::Draw(Screen &theScreen){

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

const std::string &BreakoutStartScene::GetSceneName() const
{
    static std::string name = "Break things!";
    return name;
}
