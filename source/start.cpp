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

using namespace std;

// general state
char programName[] = "Makefile Madness";
enum screenType screen;
int backgroundTexture;
int keyboardTexture;
double lastTime;

//button info
const int buttonHeight = 118;
const int bufferHeight = buttonHeight / 4;
const int buttonX = 256;//x position of where button starts
const char numButtons = 6;

//Start Screen Buttons//
Button startButton("Start Game", buttonX, (bufferHeight*5 + buttonHeight*4),500, 118, GAME,START, 464);
Button loadButton("Load Makefile", buttonX, (bufferHeight*4 + buttonHeight*3),500, 118, LOAD,START, 452);
Button instructionsButton("Instructions", buttonX, (bufferHeight*3 + buttonHeight*2),500,118, INSTRUCTIONS,START, 460);
Button customizeButton("Customize Character", buttonX, (bufferHeight*2 + buttonHeight),500,118, CUSTOMIZE,START, 420);
MovingButton quitButton("Quit", buttonX, (bufferHeight),500, 118, QUIT,START, 235);

//Instruction Screen Buttons //
Button backButton("Go Back", 0,0,80,768, START, INSTRUCTIONS, 4);


// Main Button Array//
Button* Buttons[numButtons];

void quitProgram()
{
  int win = glutGetWindow();
  glutDestroyWindow(win);
  exit(0);
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
      drawTexture(backgroundTexture,0., 768., 1024., -768.);
      drawTexture(keyboardTexture,170,548,768,-200);
      //X and Space lines
      glBegin(GL_LINES);
      glLineWidth(2.5);
      glColor3f(.2,0,1);
      glVertex3f(270,320,0);
      glVertex3f(306,392,0);
      glEnd();

      glBegin(GL_LINES);
        glLineWidth(2.5);
        glColor3f(.2,0,1);
        glVertex3f(460,300,0);
        glVertex3f(396,372,0);
      glEnd();
      //Arrow Key Button Line
      glBegin(GL_LINES);
        glLineWidth(2.5);
        glColor3f(.2,0,1);
        glVertex3f(732,300,0);
        glVertex3f(732,368,0);
      glEnd();

      glBegin(GL_LINES);
        glLineWidth(2.5);
        glColor3f(.2,0,1);
        glVertex3f(630,300,0);
        glVertex3f(696,368,0);
      glEnd();

      glBegin(GL_LINES);
        glLineWidth(2.5);
        glColor3f(.2,0,1);
        glVertex3f(840,300,0);
        glVertex3f(765,368,0);
      glEnd();

      glBegin(GL_LINES);
        glLineWidth(2.5);
        glColor3f(.2,0,1);
        glVertex3f(760,600,0);
        glVertex3f(728,392,0);
      glEnd();
      //F1 Button line
      glBegin(GL_LINES);
        glLineWidth(2.5);
        glColor3f(.2,0,1);
        glVertex3f(250,623,0);
        glVertex3f(250,525,0);
      glEnd();

      for (short int i=0; i<numButtons; ++i) {
        if(Buttons[i]->active == screen)
          Buttons[i]->draw();
      }

      /* draw text -- Kalpit will make an image for this */
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

    case QUIT:
      drawTexture(backgroundTexture, 0.0, 768.0,1024., -768.);
      quitButton.move();
      quitButton.active = QUIT; // change to "quit screen", not just start
      for (short int i=0; i<numButtons; ++i)
        if(Buttons[i]->active == screen)
          Buttons[i]->draw();
      break;
      // the actual quit is handled in the mouse button press
      //
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
            if (screen == QUIT && Buttons[i]->active == QUIT)
              // quit button, and already pressed once
              quitProgram();
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
  cerr <<"("<<x<<","<<y<<")"<<endl;
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
    if ( screen == QUIT ) {
      glutPostRedisplay();
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

int main()
{
  lastTime = getCurrentTime();

  screen = START;
  init_buttons();

  init_gl_window();
}
