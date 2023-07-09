#ifndef CONSTANTS_H
#define CONSTANTS_H

#include "color.h"
#include "timer.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int MAGNIFICATION = 2;
const int FRAME_DELAY = 1000 / 60;

static unsigned int NUM_CIRCLE_SEGMENTS = 30;

const float PI = 3.14159f;
const float TAU = 2.0f * PI;

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

#endif