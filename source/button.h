#ifndef _BUTTON_
#define _BUTTON_

#include <GL/glut.h>
#include <string.h>

#include "ColorPoint2.h"
#include "globaldefs.h"

class Button {
private:
  int width, height; // see also start.cpp
  int labelStartX;
  string label;
  Color color;
protected:
  int x, y;
  virtual void move() {}; // only used in subclasses
public:
  enum screenType screen;
  enum screenType active;
  bool IsPressed, overButton;

  Button(string l, int xx, int yy,int w, int h, enum screenType s,enum screenType p, int lx);

  void draw();
  bool onButton(int, int);
};

class MovingButton: public Button {
private:
  bool wasClicked; // whether the user has already selected it once
public:
 MovingButton(string l, int xx, int yy,int w, int h, enum screenType s, enum screenType p, int lx) :
  Button(l, xx, yy, w, h, s, p, lx) { wasClicked = false; }

  void move();
};

#endif
