#include "arcadeScene.h"

ArcadeScene::ArcadeScene(){


}

void ArcadeScene::Init (){

    ButtonAction action;
    MouseButtonAction mouseAction;

    mouseAction.mouseButton = GameController::LeftMouseButton();
    mouseAction.mouseInputAction = [] (InputState state, const MousePosition& position){

        if (GameController::IsPressed(state))
        {
            std::cout << "Left Mouse button pressed!" << std::endl;
        }
    };

    action.key = GameController::ActionKey();
    action.action = [](uint32_t dt, InputState state){

        if (GameController::IsPressed(state))
        {
            std::cout << "Action button is pressed" << std::endl;
        }
    };

    sGameController.AddInputActionForKey(action);
    sGameController.AddMouseButtonAction(mouseAction);
    sGameController.SetMouseMovedAction([] (const MousePosition& position){

        std::cout << "Mouse position x: " << position.xPos << "y: " << position.yPos << std::endl;
    });
}

void ArcadeScene::Update(uint32_t dt){


}

void ArcadeScene::Draw(Screen& theScreen){

    // Shapes
    Triangle triangle = {Vector2D (60, 10), Vector2D (10, 110), Vector2D (110,110)};
    Rectangle rectangle = {Vector2D(theScreen.Width()/2-100, theScreen.Height()/2-100),150,200};
    Circle circle = {Vector2D(theScreen.Width()/2 +50, theScreen.Height()/2 -150), 80};

    // Render
    theScreen.Draw (triangle, Lilac(), true, Lilac());
    theScreen.Draw (rectangle, Green(), true, Green());
    theScreen.Draw (circle, Color (245, 190, 100, 100), true, Color (245, 190, 100, 100));
}

const std::string& ArcadeScene::GetSceneName() const{

    static std::string sceneName = "Arcade Scene";
    return sceneName;
}

std::unique_ptr<Scene> ArcadeScene::GetScene(eGame game){

    switch (game)
    {
    case TETRIS:
        /* code */
        break;
    
    case BREAK_OUT:
        /* code */
        break;
    
    case ASTEROIDS:
        /* code */
        break;

    case PACMAN:
        /* code */
        break;

    default:
        break;
    }

    return nullptr;
}