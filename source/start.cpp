#include <iostream>
#include <iomanip>
#include <math.h>
#include <sstream>
#include <stdlib.h>
#include <vector>

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
int WIDTH = 1024;  // width of the user window
int HEIGHT = 768;  // height of the user window
char programName[] = "Makefile Madness";
enum screenType screen;
int backgroundTexture;

//button info
const int buttonHeight = 118;
const int bufferHeight = buttonHeight / 4;
const int buttonX = 256;//x position of where button starts
const char numButtons = 5;

Button startButton("Start Game", buttonX, (bufferHeight*5 + buttonHeight*4), GAME, 464);
Button loadButton("Load Makefile", buttonX, (bufferHeight*4 + buttonHeight*3), LOAD, 452);
Button instructionsButton("Instructions", buttonX, (bufferHeight*3 + buttonHeight*2), INSTRUCTIONS, 460);
Button customizeButton("Customize Character", buttonX, (bufferHeight*2 + buttonHeight), CUSTOMIZE, 420);
Button quitButton("Quit", buttonX, (bufferHeight), QUIT, 490);
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
      for (short int i=0; i<numButtons; ++i)
        Buttons[i]->draw();
      glutSwapBuffers();
      break;
    case GAME:
      drawTexture(backgroundTexture, 0.0, 768.0, 1024., -768.);
      glutSwapBuffers();
      break;
    case LOAD:
    case INSTRUCTIONS:
      drawTexture(backgroundTexture, 0.0, 768.0, 1024., -768);
      glutSwapBuffers();
      break;
    case CUSTOMIZE:
      drawTexture(backgroundTexture, 0.0, 768.0,1024., -768.);
      glutSwapBuffers();
      break;
    case QUIT:
      quitProgram();
    default:
      cerr << "This screen not defined yet!" << endl;
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
    case 'q':
    case 'Q':
    case 27:
      quitProgram();
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
        if (Buttons[i]->onButton(x,y)) {
          Buttons[i]->IsPressed = true;
          screen = Buttons[i]->screen;
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

// the reshape function handles the case where the user changes the size
//   of the window.  We need to fix the coordinate
//   system, so that the drawing area is still the unit square.
void reshape(int w, int h)
{
   glViewport(0, 0, (GLsizei) w, (GLsizei) h);
   WIDTH = w;  HEIGHT = h;
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glOrtho(0., WIDTH-1, 0., HEIGHT-1, -1.0, 1.0);
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

  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  glutKeyboardFunc(keyboard);
  glutSpecialFunc(special_keyboard);
  glutMouseFunc(mouse);
  glutMotionFunc(mouse_motion);
  glutPassiveMotionFunc(mouse_motion);
  glutMainLoop();
}

void init_buttons()
{
  // to change the number of buttons, adjust numButtons global variable
  Buttons[0] = &startButton;
  Buttons[1] = &loadButton;
  Buttons[2] = &instructionsButton;
  Buttons[3] = &customizeButton;
  Buttons[4] = &quitButton;
  for (short int i=0; i<numButtons; ++i) {
    Buttons[i]->IsPressed = false; Buttons[i]->overButton = false;
  }
}

int main()
{
  screen = START;
  init_buttons();

  init_gl_window();
}
