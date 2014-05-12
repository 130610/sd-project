#ifndef _GLOBALDEFS_
#define _GLOBALDEFS_

enum screenType { START=1,GAME, LOAD, INSTRUCTIONS, CUSTOMIZE, QUIT_MOVE, QUIT_DATE, CHECK_QUIT_DATE };

const int WIDTH = 1024;
const int HEIGHT = 768;
const double FPS = 20;
const int METER_LENGTH = 20;
const bool GRAVITY = false;
const bool FRICTION = false;
const double FRICTION_FACTOR = .2;
const double POWER_TIME = .5;

#endif
