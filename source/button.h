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
  bool keepPressed;
  virtual void move() {}; // only used in subclasses
public:
  enum screenType screen;
  enum screenType active;
  bool IsPressed, overButton;

  Button (string label, int x, int y, int w, int h,
	  enum screenType screen, enum screenType active, int labelStartX, bool kP);

  virtual void draw();
  void drawButton();
  string getLabel() { return label; }
  bool onButton(int, int);
  bool getkeepPressed()
  {
    return keepPressed;
  }
  void changekeepPressed(bool x)
  {
    keepPressed = x;
  }
};

class MovingButton: public Button {
public:
 MovingButton(string l, int xx, int yy,int w, int h, enum screenType s, enum screenType p, int lx, bool kP) :
  Button(l, xx, yy, w, h, s, p, lx, kP) { }

  void draw();
  void move();
};

#endif
