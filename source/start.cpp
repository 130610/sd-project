#include <iostream>
#include <iomanip>
#include <sstream>
#include <vector>
#include <stdlib.h>
#include <math.h>

#ifdef MACOSX
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "texture.h"
#include "button.h"
#include "ColorPoint2.h"
#include "text.h"

using namespace std;

void init_gl_window();

// general state
int WIDTH = 1024;  // width of the user window
int HEIGHT = 768;  // height of the user window
char programName[] = "Makefile Madness";
enum screenType { START=1, GAME, LOAD, INSTRUCTIONS, CUSTOMIZE, QUIT } screen;
int backgroundTexture;

//button info
const int buttonHeight = 118;
const int bufferHeight = buttonHeight / 4;
const int buttonX = 256;//x position of where button starts
const Color buttonColor(0.5255, 0.5020, 0.5294); // gray
Button startButton("Start Game", buttonX, (bufferHeight*5 + buttonHeight*4), buttonColor, 464);
Button loadButton("Load Makefile", buttonX, (bufferHeight*4 + buttonHeight*3), buttonColor, 452);
Button instructionsButton("Instructions", buttonX, (bufferHeight*3 + buttonHeight*2), buttonColor, 460);
Button customizeButton("Customize Character", buttonX, (bufferHeight*2 + buttonHeight), buttonColor, 420);
Button quitButton("Quit", buttonX, (bufferHeight), buttonColor, 490);
Button* Buttons[5];

void display()
{
  // clear the buffer
  glClear(GL_COLOR_BUFFER_BIT);

  switch(screen) {
    case START:
      glClear(GL_COLOR_BUFFER_BIT);
      drawTexture(backgroundTexture, 0.0, 768.0, 1024.0, -768.0);
      startButton.draw();
      loadButton.draw();
      instructionsButton.draw();
      customizeButton.draw();
      quitButton.draw();
      glutSwapBuffers();
      break;
    case GAME:
      glClear(GL_COLOR_BUFFER_BIT);
      drawTexture(backgroundTexture, 0.0, 768.0, 1024., -768.);
      glutSwapBuffers();
      break;
    case LOAD:
    case INSTRUCTIONS:
    case CUSTOMIZE:
    case QUIT:
      glClear(GL_COLOR_BUFFER_BIT);
      drawTexture(backgroundTexture, 0.0, 768.0,1024., -768.);
      glutSwapBuffers();
      break;
    default:
      cerr << "Not defined yet!" << endl;
      break;
  }

  // tell the graphics card that we're done-- go ahead and draw!
  glutSwapBuffers();
}

// process keyboard events
void keyboard( unsigned char c, int x, int y )
{
  int win = glutGetWindow();
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
      // get rid of the window (as part of shutting down)
      glutDestroyWindow(win);
      exit(0);
      break;
    case '\b':
      break;
    default:
      break;
  }
  glutPostRedisplay();
}

// process "special" keyboard events (those having to do with arrow keys)
void special_keyboard(int key,int x, int y)
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
      if ( startButton.onButton(x,y) ) {
        startButton.IsPressed = true;
        screen = GAME;
      }
      if ( loadButton.onButton(x,y)) {
        loadButton.IsPressed = true;
        screen = LOAD;
      }
      if ( instructionsButton.onButton(x,y)) {
        instructionsButton.IsPressed=true;
        screen = INSTRUCTIONS;
      }
      if (customizeButton.onButton(x,y)) {
        customizeButton.IsPressed=true;
        screen = CUSTOMIZE;
      }
      if (quitButton.onButton(x,y)) {
        quitButton.IsPressed = true;
        screen = QUIT;
      }
    }
    else { // mouse release
      if ( startButton.onButton(x,y) && startButton.IsPressed )
        startButton.IsPressed = false;
      if ( loadButton.onButton(x,y) && loadButton.IsPressed )
        loadButton.IsPressed = false;
      if (instructionsButton.onButton(x,y) && instructionsButton.IsPressed)
        instructionsButton.IsPressed = false;
      if (customizeButton.onButton(x,y) &&  customizeButton.IsPressed)
        customizeButton.IsPressed = false;
      if (quitButton.onButton(x,y) && quitButton.IsPressed)
        quitButton.IsPressed = false;
    }
  }
  else if ( GLUT_RIGHT_BUTTON == mouseButton ) { }

  glutPostRedisplay();
}

//mouse_motion function...called from init function
//called when mouse is being dragged, ang gives the current location
// of the mouse
void mouse_motion(int x,int y)
{
  // the mouse button is pressed, and the mouse is moving....
  if ( startButton.IsPressed ) {}
  else if ( loadButton.IsPressed) {}
  else if (instructionsButton.IsPressed) {}
  else if(customizeButton.IsPressed) {}
  else if(quitButton.IsPressed) {}
  else {
    if ( startButton.onButton(x,y) ) {
      startButton.overButton = true;
    }
    else {
      startButton.overButton = false;
    }

    if( loadButton.onButton(x,y))
      loadButton.overButton = true;
    else
      loadButton.overButton=false;

    if( instructionsButton.onButton(x,y))
      instructionsButton.overButton =true;
    else
      instructionsButton.overButton=false;

    if(customizeButton.onButton(x,y))
      customizeButton.overButton=true;
    else
      customizeButton.overButton = false;
    if(quitButton.onButton(x,y))
      quitButton.overButton = true;
    else
      quitButton.overButton = false;
    }
  glutPostRedisplay();
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


int main()
{
  screen = START;
  startButton.IsPressed = false; startButton.overButton=false;
  loadButton.IsPressed = false; loadButton.overButton= false;
  instructionsButton.IsPressed = false; instructionsButton.overButton = false;
  customizeButton.IsPressed = false; customizeButton.overButton = false;
  quitButton.IsPressed = false; quitButton.overButton = false;

  init_gl_window();
}
