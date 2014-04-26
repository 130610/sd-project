#ifdef MACOSX
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

/* Source:
 * http://stackoverflow.com/questions/11190205/opengl-display-animation-and-draw-text
 */

void drawBitmapText(char *string,float x,float y,float z)
{
  char *c;
  glRasterPos3f(x, y,z);

  for (c=string; *c != '\0'; c++) {
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
  }
}

void drawStrokeText(char*string,int x,int y,int z)
{
  char *c;
  glPushMatrix();
  glTranslatef(x, y+8,z);
  glScalef(0.09f,-0.08f,z);

  for (c=string; *c != '\0'; c++)
  {
    glutStrokeCharacter(GLUT_STROKE_ROMAN , *c);
  }
  glPopMatrix();
}
