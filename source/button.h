#ifndef _BUTTON_
#define _BUTTON_

#include <GL/glut.h>
#include <string.h>

#include "ColorPoint2.h"
#include "globaldefs.h"

class Button {
private:
  int x, y;
  const int width = 500, height = 118; // see also start.cpp
  int labelStartX;
  string label;
  Color color;
public:
  enum screenType screen;
  enum screenType active;
  bool IsPressed, overButton;

  Button(string l, int xx, int yy, enum screenType s,enum screenType p, int lx);

  void draw();
  bool onButton(int, int);
};

#endif
