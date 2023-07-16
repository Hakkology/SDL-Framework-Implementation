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

    std::cout << "Break Out Game Init()" << std::endl;
}

void BreakOut::Update(uint32_t dt){

    std::cout << "Break Out Game Update()" << std::endl;
}

void BreakOut::Draw(Screen &screen){

    std::cout << "Break Out Game Draw()" << std::endl;
}

std::string BreakOut::GetName() const{

    return "Break Out!";
}
