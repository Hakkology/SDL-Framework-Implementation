#include "notimplementedScene.h"
#include "app.h"
#include "rectangle.h"
#include "inputaction.h"
#include "screen.h"

void NotImplementedScene::Init(){

    ButtonAction backAction;
    backAction.key = GameController::CancelKey();
    backAction.action = [](uint32_t dt, InputState state){

        if (GameController::IsPressed(state))
        {
            App::Singleton().PopScene();
        }
    };
    sGameController.AddInputActionForKey(backAction);
}

void NotImplementedScene::Update(uint32_t dt){

}

void NotImplementedScene::Draw(Screen &screen){

    const BmpFont& font = App::Singleton().GetFont();

    Rectangle rect = {Vector2D::Zero, App::Singleton().Width(), App::Singleton().Height()/3};
    Vector2D textDrawPosition;
    textDrawPosition = font.GetDrawPosition("GAME STATION", rect, BFXA_CENTER, BFYA_CENTER);

    screen.Draw(font, "GAME STATION", textDrawPosition, Orange());

    Triangle triangle = {Vector2D (20, 30), Vector2D (10, 130), Vector2D (60,20)};
    screen.Draw (triangle, Lilac(), true, Lilac());
    Circle circle = {Vector2D(screen.Width()/2 +150, screen.Height()/2 -50), 60};
    screen.Draw (circle, Green(), true, Green());
    Rectangle rectangle = {Vector2D(screen.Width()/2-60, screen.Height()/2+75),120,45};
    screen.Draw (rectangle, Blue(), true, Blue());

    Rectangle warnRect = {Vector2D::Zero, App::Singleton().Width(), App::Singleton().Height()};

    Vector2D warningTextDrawPosition;
    warningTextDrawPosition = font.GetDrawPosition(GetSceneName(), warnRect, BFXA_CENTER, BFYA_CENTER);

    screen.Draw(font, GetSceneName(), warningTextDrawPosition, Red());
}

const std::string &NotImplementedScene::GetSceneName() const{

    static std::string name = "Not Implemented";
    return name;
}
