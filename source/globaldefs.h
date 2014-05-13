#ifndef _GLOBALDEFS_
#define _GLOBALDEFS_

enum screenType { START=1,GAME, LOAD, INSTRUCTIONS, CUSTOMIZE, QUIT_MOVE, QUIT_DATE, CHECK_QUIT_DATE };

/* window properties */
const int WIDTH = 1024;
const int HEIGHT = 768;
const double FPS = 20;

/* Target drawing properties */
const int MAX_X_FACTOR = 250;
const int MAX_Y_FACTOR = 800;
const int BOX_WIDTH = 150;
const int BOX_HEIGHT = 250;
const int WRAP = 3; //WIDTH / MAX_X_FACTOR;

/* physics switches */
const int METER_LENGTH = 20;
const bool GRAVITY = true;
const bool FRICTION = false;
const double FRICTION_FACTOR = .2;
const double POWER_TIME = .5;

#endif
