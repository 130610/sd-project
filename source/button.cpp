#include "button.h"
#include "text.h"

void Button::draw() {
  int x0 = min(x, x + width);
  int x1 = max(x, x + width);
  int y0 = min(y, y + height);
  int y1 = max(y, y + height);

  // button

 //buttonpress
  if( IsPressed ) glColor3f(1., 1., 1.);//turns white;
  else if ( overButton ) glColor3f(0., 1., 0.);
  else glColor3f(color.red, color.green, color.blue);
  
  glBegin(GL_QUADS);
    glVertex2f(x0, y0);
    glVertex2f(x1, y0);
    glVertex2f(x1, y1);
    glVertex2f(x0, y1);
  glEnd();

  //border
  glColor3f(0,0,0);
  glBegin(GL_LINE_STRIP);
    glVertex2f(x0, y0);
    glVertex2f(x1, y0);
    glVertex2f(x1, y1);
    glVertex2f(x0, y1);
    glVertex2f(x0, y0);
  glEnd();

  //text
  char * bText = new char[label.size() + 1];
  copy(label.begin(), label.end(), bText);
  bText[label.size()] = '\0';
  drawBitmapText(bText,labelStartX, y + (height / 2) - 4,0);
  delete[] bText;

 
}

bool Button::onButton(int xmousepos, int ymousepos)
  {
    
    int newymousepos = 768-ymousepos; /*mouse position and graphics 
					position have different point 
					of origin*/
    return xmousepos>= x && xmousepos<=(x+width) && newymousepos >=y &&
      newymousepos <= (y+height);
    
  }
