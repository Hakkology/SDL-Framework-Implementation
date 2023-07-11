#include "arcadeScene.h"

ArcadeScene::ArcadeScene(){


}

void ArcadeScene::Init (){


}

void ArcadeScene::Update(uint32_t dt){


}

void ArcadeScene::Draw(Screen& theScreen){

    Triangle triangle = {Vector2D (60, 10), Vector2D (10, 110), Vector2D (110,110)};
    Rectangle rectangle = {Vector2D(theScreen.Width()/2-100, theScreen.Height()/2-100),150,200};
    Circle circle = {Vector2D(theScreen.Width()/2 +50, theScreen.Height()/2 -150), 80};
    std::cout << "Shapes created...\n";

    // Render
    theScreen.Draw (triangle, Lilac(), true, Lilac());
    theScreen.Draw (rectangle, Green(), true, Green());
    theScreen.Draw (circle, Color (245, 190, 100, 100), true, Color (245, 190, 100, 100));
}

const std::string& ArcadeScene::GetSceneName() const{

    return "Arcade Scene";
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