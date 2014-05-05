#ifdef MACOSX
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <string>
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

void drawText(int x, int y, string text)
{
  glColor3f(0, 0, 0);
  glRasterPos2f((float) x, (float) y);
  for (unsigned i = 0; i < text.length(); i++)
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, text[i]);
}
