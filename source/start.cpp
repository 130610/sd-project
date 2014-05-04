#define DEBUG // allows quitting with 'q' to avoid the quit sequence

#include <iostream>
#include <iomanip>
#include <math.h>
#include <sstream>
#include <stdlib.h>
#include <vector>
#include <sys/time.h>

#ifdef MACOSX
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "button.h"
#include "ColorPoint2.h"
#include "globaldefs.h"
#include "text.h"
#include "texture.h"
#include "start.h"
#include "InstructionLines.h"
#include "target.h"


using namespace std;

// root target
Target **rootTarget;
const char *defaultMakefile = "Makefile.level";

// general state
char programName[] = "Makefile Madness";
enum screenType screen;
int backgroundTexture;
int keyboardTexture;
int koalaTexture;
double lastTime;

//button info
const int buttonHeight = 118;
const int bufferHeight = buttonHeight / 4;
const int buttonX = 256;//x position of where button starts
const char numButtons = 6;

// quit textbox info
bool overQuitTextBox = false;
string textInQuitBox = "";
double quitTextBox1[] = { 320, 30,   200, 40 };  // outer box for text
double quitTextBox2[] = { 325, 35,   190, 30 };  // inner box for text
const unsigned int MAX_NUM_CHARS_IN_QUIT_TEXTBOX = 20;

//Start Screen Buttons//
Button startButton("Start Game", buttonX, (bufferHeight*5 + buttonHeight*4),500, 118, GAME,START, 464);
Button loadButton("Load Makefile", buttonX, (bufferHeight*4 + buttonHeight*3),500, 118, LOAD,START, 452);
Button instructionsButton("Instructions", buttonX, (bufferHeight*3 + buttonHeight*2),500,118, INSTRUCTIONS,START, 460);
Button customizeButton("Customize Character", buttonX, (bufferHeight*2 + buttonHeight),500,118, CUSTOMIZE,START, 420);
MovingButton quitButton("Quit", buttonX, (bufferHeight),500, 118, QUIT_MOVE,START, 235);

//Instruction Screen Buttons //
Button backButton("Go Back", 0,0,80,768, START, INSTRUCTIONS, 4);


// Main Button Array//
Button* Buttons[numButtons];


//Koala Main screen global variables
float koalax=10;
float koalay=120;
float mouseposx;
float mouseposy;
float theta;
float koalatargetx=koalax;
float koalatargety=koalay;
bool atTarget=true;

void quitProgram()
{
  int win = glutGetWindow();
  glutDestroyWindow(win);
  exit(0);
}

void drawInstructions()
{
  drawTexture(backgroundTexture,0., 768., 1024., -768.);
  drawTexture(keyboardTexture,170,548,768,-200);

  Text xt1(120,310,"X button allows the");
  Text xt2(120,290,"user to launch the Koala");
  LegendItem xKey(270,306,320,392,2.5,xt1,xt2);

  Text spacet1(400, 280, "Holding the space bar");
  Text spacet2(400, 260, "allows user to set the");
  Text spacet3(400, 240, "power of the Koala launch");
  LegendItem spaceKey(460,396,300,372,2.5, spacet1, spacet2, spacet3);

  Text darrowt1(732, 300, "Pressing the down arrow");
  Text darrowt2(732, 280, "allows user to set");
  Text darrowt3(732, 260, "the trajectory of the launch");
  LegendItem darrowKey(732,732,300,368,2.5, darrowt1, darrowt2, darrowt3);

  Text uarrowt1(760, 640, "Pressing the up arrow");
  Text uarrowt2(760, 620, "allows user to set");
  Text uarrowt3(760, 600, "the trajectory of the launch");
  LegendItem uarrowKey(760,728,600,392,2.5, uarrowt1, uarrowt2, uarrowt3);

  Text f1t1(230, 643, "Pressing F1 returns you");
  Text f1t2(230, 623, "to the start screen");
  LegendItem f1Key(250,250,632,525,2.5, f1t1, f1t2, uarrowt3);

  xKey.draw();
  spaceKey.draw();
  darrowKey.draw();
  uarrowKey.draw();
  f1Key.draw();
}

void display()
{
  // clear the buffer
  glClear(GL_COLOR_BUFFER_BIT);

  switch(screen) {
    case START:
      drawTexture(backgroundTexture, 0.0, 768.0, 1024.0, -768.0);
      for (short int i=0; i<numButtons; ++i) {
        if (Buttons[i]->active == screen)
          Buttons[i]->draw();
      }

      glutSwapBuffers();
      break;

    case GAME:
      drawTexture(backgroundTexture, 0.0, 768.0, 1024., -768.);
      for (short int i=0; i<numButtons; ++i) {
        if(Buttons[i]->active == screen)
          Buttons[i]->draw();
      }
      // Drawing the target boxes
      // Drawing the line tracking the koala launch trajectory

      // cerr<<"Tracking position: ("<<trackingx<<","<<trackingy<<")"<<endl;
      int hypotenuse;
      hypotenuse = sqrt(((mouseposx-(koalax+40))*(mouseposx-(koalax+40)))+((mouseposy-(koalay-40))*(mouseposy-(koalay-40))));
      theta = atan((mouseposy-(koalay-40))/(mouseposx-(koalax+40)));
      //cerr <<hypotenuse<<endl;
      //cerr <<theta <<endl;
      if(hypotenuse >=100)
	hypotenuse =100;
      glLineStipple(1, 0xAAAA);
      glEnable(GL_LINE_STIPPLE);
      glBegin(GL_LINES);
       glVertex3f(koalax+40, koalay-40, 0);
       glVertex3f(mouseposx ,mouseposy,0);
      glEnd();

      //Drawing the Koala
      drawTexture(koalaTexture,koalax,koalay,100,-100);
      glutSwapBuffers();
      break;

    case LOAD:
      drawTexture(backgroundTexture, 0., 768.,1024., -768.);
      for (short int i=0; i<numButtons; ++i) {
        if(Buttons[i]->active == screen)
          Buttons[i] -> draw();
      }
      glutSwapBuffers();
      break;

    case INSTRUCTIONS:
      drawInstructions();

      for (short int i=0; i<numButtons; ++i) {
        if(Buttons[i]->active == screen)
          Buttons[i]->draw();
      }

      glutSwapBuffers();
      break;
    case CUSTOMIZE:
      drawTexture(backgroundTexture, 0.0, 768.0,1024., -768.);
      for (short int i=0; i<numButtons; ++i) {
        if(Buttons[i]->active == screen)
          Buttons[i]->draw();
      }
      glutSwapBuffers();
      break;

    case QUIT_MOVE:
      drawTexture(backgroundTexture, 0.0, 768.0,1024., -768.);
      quitButton.move();
      quitButton.active = QUIT_MOVE; // change to "quit screen", not just start
      quitButton.screen = QUIT_DATE;
      for (short int i=0; i<numButtons; ++i)
        if(Buttons[i]->active == screen)
          Buttons[i]->draw();
      break;
      // the actual quit is handled in the mouse button press
    case QUIT_DATE:
      {
      cerr << "I'm on the quit date screen" << endl;
      quitProgram();
      break;
      }
    default:
      cerr << "This screen not defined (yet?)." << endl;
      break;
  }

  // tell the graphics card that we're done-- go ahead and draw!
  glutSwapBuffers();
}

// process keyboard events
void keyboard(unsigned char c, int x, int y)
{
  switch(c) {
  case 'x':
    koalatargetx=mouseposx;
    koalatargety=mouseposy;
    break;
    case 'g':
    case 'G':
      if (screen == START)
        screen = GAME;
      else if (screen == GAME)
        screen = START;
      break;
#ifdef DEBUG
    case 'q':
    case 'Q':
    case 27:
      quitProgram();
#endif
    case '\b':
    default:
      break;
  }
  glutPostRedisplay();
}

// process "special" keyboard events
void special_keyboard(int key, int x, int y)
{
  switch (key) {
    case GLUT_KEY_F1:
      screen = START;
      break;
  }
  glutPostRedisplay();
}

// The mouse function is called when a mouse button is pressed down or released
void mouse(int mouseButton, int state, int x, int y)
{
  if ( GLUT_LEFT_BUTTON == mouseButton ) {
    if ( GLUT_DOWN == state ) { // mouse press
      for (short int i=0; i<numButtons; ++i) {
        if(Buttons[i]->active == screen) {
          if (Buttons[i]->onButton(x,y)) {
            Buttons[i]->IsPressed = true;
            if (screen == QUIT_MOVE && Buttons[i]->active == QUIT_MOVE) {
              // quit button, and already pressed once; move to date part
              screen = QUIT_DATE;
              Buttons[i]->active = QUIT_DATE;
            }
            else
              screen = Buttons[i]->screen;
          }
        }
      }
	
    }
    else { // mouse release
      for (short int i=0; i<numButtons; ++i) {
        if ( Buttons[i]->onButton(x,y) && Buttons[i]->IsPressed )
          Buttons[i]->IsPressed = false;
      }
    }
    //else if ( GLUT_RIGHT_BUTTON == mouseButton ) { }

    glutPostRedisplay();
  }
}

//mouse_motion function...called from init function
//called when mouse is being dragged, and gives the current location
// of the mouse
void mouse_motion(int x, int y)
{
#ifdef DEBUG
  // show coordinates of mouse pointer
  //cerr <<"Mouse position: ("<<x<<","<<y<<")"<<endl;
  mouseposx = x;
  mouseposy=768-y;
#endif

  // is the mouse button currently depressed over any screen button?
  bool aButtonIsPressed = false;
  for (short int i=0; i<numButtons; ++i) {
    if (Buttons[i]->IsPressed) {
      aButtonIsPressed = true;
      break;
    }
  }

  // if not, for each button, determine if it's moused over
  // this is used both to set and unset this status
  if ( !aButtonIsPressed ) {
    for (short int i=0; i<numButtons; ++i) {
      if ( Buttons[i]->onButton(x,y) )
        Buttons[i]->overButton = true;
      else
        Buttons[i]->overButton = false;
    }
  glutPostRedisplay();
  }
}

// the init function sets up the graphics card to draw properly
void init(void)
{
  // clear the window to black
  glClearColor(0.0, 0.0, 0.0, 0.0);
  glClear(GL_COLOR_BUFFER_BIT);

  // set up the coordinate system:  number of pixels along x and y
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0., WIDTH-1, 0., HEIGHT-1, -1.0, 1.0);

  // set up how points and lines will be drawn.  The following
  //  commands make points and lines look nice and smooth.
  glPointSize(3);
  glLineWidth(1.5);
  glEnable(GL_POINT_SMOOTH);
  glEnable(GL_LINE_SMOOTH);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glHint(GL_LINE_SMOOTH_HINT, GL_DONT_CARE);

  // welcome message
  cout << "Welcome to " << programName << "." << endl;
  cout << "To quit the entire program press the 'q' key"<<endl;
  cout << "To return to start screen press the F1 key"<<endl;
}

void init_gl_window()
{
  char *argv[] = {programName};
  int argc = sizeof(argv) / sizeof(argv[0]);
  glutInit(&argc, argv);
  glutInitDisplayMode( GLUT_RGB | GLUT_DOUBLE );
  glutInitWindowSize(WIDTH,HEIGHT);
  glutInitWindowPosition(100,100);
  glutCreateWindow(programName);
  init();

  backgroundTexture = loadTexture("../images/background.pam");
  keyboardTexture = loadTexture("../images/keyboard.pam");
  koalaTexture = loadTexture("../images/Koala.pam");

  glutDisplayFunc(display);
  glutKeyboardFunc(keyboard);
  glutSpecialFunc(special_keyboard);
  glutMouseFunc(mouse);
  glutMotionFunc(mouse_motion);
  glutPassiveMotionFunc(mouse_motion);
  glutIdleFunc(idle);
  glutMainLoop();
}

double getCurrentTime()
{
  struct timeval tv = {0,0};
  struct timezone tz;
  gettimeofday(&tv, &tz);
  // cout << "tv is " << tv.tv_sec << " micro " << tv.tv_usec << endl;
  return tv.tv_sec + tv.tv_usec/(double)1000000.;
}

void idle()
{
  // figure out whether it is time to change the counter.
  //   we want the counter to change once per second, so we want the
  //   elapsed time (since the beginning of the program) to be 
  //   the same as the elapsedTime (rounded down)
  double now = getCurrentTime();
  double elapsedTime = now - lastTime;
  if ( elapsedTime > .05 ) {
    lastTime = now;
    if ( screen == QUIT_MOVE ) {
      glutPostRedisplay();
    }
  }
  if (elapsedTime > .05)
    {
      if( screen == GAME)
	{
	  if(!(koalax==koalatargetx && koalay == koalatargety))
	    {
	    
	      koalax+=(koalatargetx-koalax)/15; //It's never really stopping...but since it's integer division it's going essentially to zero.
	      koalay+=(koalatargety-koalay)/15;
	      glutPostRedisplay();
	    }
	}
    }
}


void init_buttons()
{
  // to change the number of buttons, adjust numButtons global variable
  Buttons[0] = &startButton;
  Buttons[1] = &loadButton;
  Buttons[2] = &instructionsButton;
  Buttons[3] = &customizeButton;
  Buttons[4] = &quitButton;
  Buttons[5] = &backButton;
  for (short int i=0; i<numButtons; ++i) {
    Buttons[i]->IsPressed = false; Buttons[i]->overButton = false;
  }
}

void init_targets(int argc, char **argv)
{
  
  string name;
  if (argc >= 2) {
    rootTarget = parseTargets(argv[argc]);
  } else {
    rootTarget = parseTargets(defaultMakefile);
  }

  rootTarget[0]->initPositions();
}

int main(int argc, char **argv)
{
  lastTime = getCurrentTime();

  screen = START;
  init_buttons();
  init_targets(argc, argv);

  init_gl_window();
}
