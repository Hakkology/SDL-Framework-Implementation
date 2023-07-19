 #include "breakout.h"


 /*
 
    Paddle
        - Can move side to side (by the User)
        - Stops at the edge of the screen
        - Width and height
        - Bounces the ball
            -Bounces the ball differently based on the position that was hit on the paddle.
    
    Ball
        -Bounces off of the walls and the paddle
        - Width and height
        - Velocity position

    Blocks
        - part of the levels
        - blocks have HPs - one hit by the ball is -1 HP
        - Color and position, width and height
        - bounces the ball
    
    Level
        - container that holds all of the blocks
        - Should be able to load a level from levels.txt file
        - handle collisions
        - contain the walls/edges of the screen
        - reset the level
    
    Game
        - contains all objects, paddle, ball and levels
        - player which has 3 lives
        - Game states, -serve the ball, In Game, Game Over
        - Reset the game

 */

void BreakOut::Init(GameController &controller){

    controller.ClearAll();
    ResetGame();

    ButtonAction leftKeyAction;

    leftKeyAction.key = GameController::LeftKey();
    leftKeyAction.action = [this](uint32_t dt, InputState state){

        if (GameController::IsPressed(state))
        {
            bPaddle.SetMovementDirection(PaddleDirection::LEFT);
        }
        else
        {
            bPaddle.UnsetMovementDirection(PaddleDirection::LEFT);
        }
    };
    controller.AddInputActionForKey(leftKeyAction);

    ButtonAction rightKeyAction;
    
    rightKeyAction.key = GameController::RightKey();
    rightKeyAction.action = [this] (uint32_t dt, InputState state){

        if (GameController::IsPressed(state))
        {
            bPaddle.SetMovementDirection(PaddleDirection::RIGHT);
        }
        else
        {
            bPaddle.UnsetMovementDirection(PaddleDirection::RIGHT);
        }
    };
    controller.AddInputActionForKey(rightKeyAction);

}

void BreakOut::Update(uint32_t dt){

    bPaddle.Update(dt);
}

void BreakOut::Draw(Screen &screen){

    bPaddle.Draw(screen);
}

std::string BreakOut::GetName() const{

    return "Break Out!";
}

void BreakOut::ResetGame(){

    Rectangle paddleRect = {Vector2D(App::Singleton().Width()/2 - paddleWidth/2, App::Singleton().Height() - 3*paddleHeight), paddleWidth, paddleHeight};
    Rectangle levelBoundary = {Vector2D::Zero, App::Singleton().Width(), App::Singleton().Height()};

    bPaddle.Init(paddleRect, levelBoundary);
}
