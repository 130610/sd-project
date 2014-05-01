#ifndef _BUTTON_
#define _BUTTON_

#include <GL/glut.h>
#include <string.h>

#include "ColorPoint2.h"
#include "globaldefs.h"

class Button {
protected:
  int x, y;
  int width, height; // see also start.cpp
  string label;
  int labelStartX;
  Color color;
  virtual void move() {}; // only used in subclasses
public:
  enum screenType screen;
  enum screenType active;
  bool IsPressed, overButton;

  Button(string l, int xx, int yy,int w, int h, enum screenType s,enum screenType p, int lx);

  virtual void draw();
  void drawButton();
  bool onButton(int, int);
};

class MovingButton: public Button {
public:
 MovingButton(string l, int xx, int yy,int w, int h, enum screenType s, enum screenType p, int lx) :
  Button(l, xx, yy, w, h, s, p, lx) { }

  void draw();
  void move();
};

#endif
