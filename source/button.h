#ifndef _BUTTON_
#define _BUTTON_

#include <GL/glut.h>

#include "ColorPoint2.h"
#include <string.h>

class Button {
private:
  int x, y;
  const int width = 500, height = 118; // see also start.cpp
  int labelStartX;
  string label;
  Color color;
public:
  bool IsPressed, overButton;

  Button(string l, int xx, int yy, Color c, int lx=500)
    { x = xx; y = yy; color = c; label = l; labelStartX = lx; }

  void draw();
  bool onButton(int, int);
};

#endif

