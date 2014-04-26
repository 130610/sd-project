#ifndef _BUTTON_
#define _BUTTON_

#include <GL/glut.h>

#include "ColorPoint2.h"
#include <string.h>

class Button {
private:
  int x, y;
  const int width = 500, height = 118; // see also start.cpp
  string label;
  Color color;

public:
  Button(string l, int xx, int yy, Color c) {
    x = xx; y = yy; color = c; label = l;
  }

  void draw() {
    int x0 = min(x, x + width);
    int x1 = max(x, x + width);
    int y0 = min(y, y + height);
    int y1 = max(y, y + height);

    glColor3f(color.red, color.green, color.blue);
    glBegin(GL_QUADS);
      glVertex2f(x0, y0);
      glVertex2f(x1, y0);
      glVertex2f(x1, y1);
      glVertex2f(x0, y1);
    glEnd();

    glColor3f(0,0,0);
    glBegin(GL_LINE_STRIP);
      glVertex2f(x0, y0);
      glVertex2f(x1, y0);
      glVertex2f(x1, y1);
      glVertex2f(x0, y1);
      glVertex2f(x0, y0);
    glEnd();

  }

};

#endif

