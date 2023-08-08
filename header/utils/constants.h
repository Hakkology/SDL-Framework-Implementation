#ifndef CONSTANTS_H
#define CONSTANTS_H

#include "color.h"
#include "vector2D.h"

const int SCREEN_WIDTH = 224;
const int SCREEN_HEIGHT = 320;
const int MAGNIFICATION = 2;
const int FRAME_DELAY = 1000 / 60;

static unsigned int NUM_CIRCLE_SEGMENTS = 48;

const float PI = 3.14159f;
const float TAU = 2.0f * PI;

const uint32_t DELTA_TIME = 15;
const uint32_t MAX_FRAME_RATE = 300;

static const Vector2D UP_DIR = {0, -1};
static const Vector2D DOWN_DIR = {0, 1};
static const Vector2D LEFT_DIR =  {-1, 0};
static const Vector2D RIGHT_DIR = {1, 0};

static Color Black() {return Color (0, 0, 0, 255);}
static Color White() {return Color (255, 255, 255, 255);}
static Color Red() {return Color (255, 0, 0, 255);}
static Color Green() {return Color (0, 255, 0, 255);}
static Color Blue() {return Color (0, 0, 255, 255);}
static Color Yellow() {return Color (255, 255, 0, 255);}
static Color Magenta() {return Color (255, 0, 255, 255);}
static Color Cyan() {return Color (37, 240, 217, 255);}
static Color Pink() {return Color (252, 197, 224, 255);}
static Color Orange() {return Color (245, 190, 100, 255);}
static Color Lilac() {return Color (160, 100, 160, 255);}

// Breakout constants

// Paddle
const float paddleVelocity = 250.0f;
static const uint32_t paddleWidth = 100;
static const uint32_t paddleHeight = 10;
const float corner_bounce_amt = 0.2f;

// Ball
static const float BALL_RADIUS = 5.0f;
const Vector2D initBallVelocity = Vector2D(200, -200);
static const float INIT_BALL_SPEED = 150;

// Blocks
static const int BLOCK_WIDTH = 16;
static const int BLOCK_HEIGHT = 8;

// Levels Path
static const std::string LEVELS_PATH = "Assets/BreakoutLevels.txt";
const int LEVEL_NO = 1;

// Game Details
const int NUM_LIVES = 3;

// Font spacings
const uint32_t FontSpacingBetweenLetters =2;
const uint32_t FontSpacingBetweenWords =5;

// Pacman Details
static const int PACMAN_MOVEMENT_SPEED = 50;
static const int PACMAN_SPAWNX_LOCATION = SCREEN_WIDTH/2;
static const int PACMAN_SPAWNY_LOCATION = 204;

const uint32_t NUM_LEVELS = 256;
const uint32_t SPRITE_HEIGHT = 16;
const uint32_t SPRITE_WIDTH = 16;

const std::string SCORE_STR = "Score  ";
const std::string PACMAN_LIFE_SPRITE_NAME = "pac_man_left_idle";
const size_t MAX_NUM_LIVES=3;
 

#endif
