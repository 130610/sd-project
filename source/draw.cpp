#ifdef MACOSX
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <string>
#include "draw.h"
using namespace std;

void drawBox(double x, double y, double width, double height,float a, float b, float c)
{
  glColor3f(a, b, c);
  glBegin(GL_POLYGON);
    glVertex2f(x, y);  // upper left
    glVertex2f(x, y + height);  // lower left
    glVertex2f(x + width, y + height);  // lower right
    glVertex2f(x + width, y);  // upper right
  glEnd();
}

void drawBox(double x, double y, double width, double height)
{
  glBegin(GL_POLYGON);
    glVertex2f(x, y);  // upper left
    glVertex2f(x, y + height);  // lower left
    glVertex2f(x + width, y + height);  // lower right
    glVertex2f(x + width, y);  // upper right
  glEnd();
}

void drawBox(int *pos)
{
  drawBox(pos[0], pos[1], pos[2], pos[3]);
}

void drawText(int x, int y, string text)
{
  glColor3f(0, 0, 0);
  glRasterPos2f((float) x, (float) y);
  for (unsigned i = 0; i < text.length(); i++)
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, text[i]);
}

void exitAll()
{
  int win = glutGetWindow();
  glutDestroyWindow(win);
  exit(0);
}


