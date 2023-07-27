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

    ButtonAction serveAction;
    
    serveAction.key = GameController::ActionKey();
    serveAction.action = [this](uint32_t dt, InputState state){

        if (bGameState == IN_SERVE)
        {
            if (GameController::IsPressed(state)){
                
                bGameState = IN_PLAY;

                if (bPaddle.IsMovingLeft())
                {
                    bBall.SetVelocity(Vector2D(-INIT_BALL_SPEED, -INIT_BALL_SPEED));
                }
                else
                {
                    bBall.SetVelocity(Vector2D(INIT_BALL_SPEED, -INIT_BALL_SPEED));
                }
            }
        }
        else if (bGameState == IN_GAME_OVER){
            
            if (GameController::IsPressed(state))
            {
                ResetGame();
            }
        }
    };

    controller.AddInputActionForKey(serveAction);

    ButtonAction leftKeyAction;

    leftKeyAction.key = GameController::LeftKey();
    leftKeyAction.action = [this](uint32_t dt, InputState state){

        if (bGameState == IN_PLAY || bGameState == IN_SERVE)
        {
            if (GameController::IsPressed(state))
            {
                bPaddle.SetMovementDirection(PaddleDirection::LEFT);
            }
            else
            {
                bPaddle.UnsetMovementDirection(PaddleDirection::LEFT);
            }
        }
    };
    controller.AddInputActionForKey(leftKeyAction);

    ButtonAction rightKeyAction;
    
    rightKeyAction.key = GameController::RightKey();
    rightKeyAction.action = [this] (uint32_t dt, InputState state){

        if (bGameState == IN_PLAY || bGameState == IN_SERVE)
        {
            if (GameController::IsPressed(state))
            {
                bPaddle.SetMovementDirection(PaddleDirection::RIGHT);
            }
            else
            {
                bPaddle.UnsetMovementDirection(PaddleDirection::RIGHT);
            }
        }
    };
    controller.AddInputActionForKey(rightKeyAction);
}

void BreakOut::Update(uint32_t dt){

    if (bGameState == IN_SERVE)
    {
        bPaddle.Update(dt, bBall);
        SetToServeState();
    }
    else if (bGameState == IN_PLAY)
    {
        bBall.Update(dt);
        bPaddle.Update(dt, bBall);

        BoundaryEdge edge;

        if (bPaddle.Bounce(bBall))
        {
            return;
        }
        
        if (bLevelBoundary.HasCollided(bBall, edge))
        {
            bBall.Bounce(edge);
        }

        GetCurrentLevel().Update(dt, bBall);
    }
}

void BreakOut::Draw(Screen &screen){

    bBall.Draw(screen);
    bPaddle.Draw(screen);
    GetCurrentLevel().Draw(screen);

    screen.Draw(bLevelBoundary.GetBoundaryRectangle(), White());
}

const std::string& BreakOut::GetName() const{

    static std::string name = "Break Out";
    return name;
}

void BreakOut::ResetGame(){

    bLevels =  BGameLevel::LoadLevelsFromFile(App::GetBasePath() + LEVELS_PATH);
    bCurrentLevel = LEVEL_NO;

    Rectangle paddleRect = {Vector2D(App::Singleton().Width()/2 - paddleWidth/2, App::Singleton().Height() - 3*paddleHeight), paddleWidth, paddleHeight};
    Rectangle levelBoundary = {Vector2D::Zero, App::Singleton().Width(), App::Singleton().Height()};

    bLevelBoundary = {levelBoundary};
    bPaddle.Init(paddleRect, levelBoundary);
    bBall.MoveTo(Vector2D(App::Singleton().Width()/2, App::Singleton().Height() * 0.7f));
    
    SetToServeState();

    //bLevel.Init(levelBoundary);
}

void BreakOut::SetToServeState(){

    bGameState = IN_SERVE;
    bBall.Stop();

    bBall.MoveTo(Vector2D(bPaddle.GetRectangle().GetCenterPoint().GetX(), bPaddle.GetRectangle().GetTopLeftPoint().GetY() - bBall.GetRadius() -1));
}
