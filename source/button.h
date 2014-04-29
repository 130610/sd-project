#ifndef _BUTTON_
#define _BUTTON_

#include <GL/glut.h>
#include <string.h>

#include "ColorPoint2.h"
#include "globaldefs.h"

class Button {
private:
  const int width = 500, height = 118; // see also start.cpp
  int labelStartX;
  string label;
  Color color;
protected:
  int x, y;
  virtual void move() {}; // only used in subclasses
public:
  enum screenType screen;
  bool IsPressed, overButton;

  Button(string l, int xx, int yy, enum screenType s, int lx);

  void draw();
  bool onButton(int, int);
};

class MovingButton: public Button {
public:
  MovingButton(string l, int xx, int yy, enum screenType s, int lx) :
    Button(l, xx, yy, s, lx) {}
  void move();
};

#endif
