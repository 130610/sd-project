#ifdef MACOSX
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "button.h"
#include "ColorPoint2.h"
#include "globaldefs.h"
#include "text.h"

Button::Button (string l, int xx, int yy,int w, int h, enum screenType s,enum screenType p, int lx)
{
  x = xx;
  y = yy;
  width =w;
  height = h;
  label = l;
  labelStartX = lx;
  screen = s;
  active = p;

  color = {0.5255, 0.5020, 0.5294};
}

void Button::drawButton()
{
  /* called from the different draw methods; the common part of the code */
  // coordinates
  int x0 = min(x, x + width);
  int x1 = max(x, x + width);
  int y0 = min(y, y + height);
  int y1 = max(y, y + height);


  // color selection, based on pressed status
  if( IsPressed ) glColor3f(1., 1., 1.); // white;
  else if ( overButton ) glColor3f(0., 1., 0.); // green
  else glColor3f(color.red, color.green, color.blue); // as defined in object

  // button
  glBegin(GL_QUADS);
    glVertex2f(x0, y0);
    glVertex2f(x1, y0);
    glVertex2f(x1, y1);
    glVertex2f(x0, y1);
  glEnd();

  // border
  glColor3f(0,0,0);
  glBegin(GL_LINE_STRIP);
    glVertex2f(x0, y0);
    glVertex2f(x1, y0);
    glVertex2f(x1, y1);
    glVertex2f(x0, y1);
    glVertex2f(x0, y0);
  glEnd();
}

void Button::draw() {
  drawButton();

  //text
  char * bText = new char[label.size() + 1];
  copy(label.begin(), label.end(), bText);
  bText[label.size()] = '\0';
  drawBitmapText(bText,labelStartX, y + (height / 2) - 4,0);
  delete[] bText;
}

void MovingButton::draw() {
  drawButton();

  //text
  char * bText = new char[label.size() + 1];
  copy(label.begin(), label.end(), bText);
  bText[label.size()] = '\0';
  drawBitmapText(bText, x + labelStartX, y + (height / 2) - 4,0);
  delete[] bText;
}

bool Button::onButton(int xmousepos, int ymousepos)
{
  int newymousepos = 768-ymousepos; /* mouse position and graphics 
                                       position have different point 
                                       of origin */
  return xmousepos>= x && xmousepos<=(x+width) && newymousepos >=y &&
         newymousepos <= (y+height);
}

void MovingButton::move()
{
  if (x < 20) x = WIDTH;
  if (y < 20) y = HEIGHT;
  x -= 4;
  y -= 4;
}
