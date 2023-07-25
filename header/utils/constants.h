#ifndef CONSTANTS_H
#define CONSTANTS_H

#include "color.h"
#include "vector2D.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int MAGNIFICATION = 2;
const int FRAME_DELAY = 1000 / 60;

static unsigned int NUM_CIRCLE_SEGMENTS = 48;

const float PI = 3.14159f;
const float TAU = 2.0f * PI;

const uint32_t DELTA_TIME = 10;
const uint32_t MAX_FRAME_RATE = 300;

static const Vector2D UP_DIR = {0, 1};
static const Vector2D DOWN_DIR = {0, -1};
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
static const float ballRadius = 5.0f;
const Vector2D initBallVelocity = Vector2D(100, -100);

#endif