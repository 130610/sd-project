#ifndef _InstructionLines_
#define _InstructionLines_
#include <math.h>
#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <vector>

#include "ColorPoint2.h"
#include "globaldefs.h"
#include "text.h"
using namespace std;

#ifdef MACOSX
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

class Line {
  int xstart;
  int xend;
  int ystart;
  int yend;
  float z; // not used in 2D drawing
  float lineWidth;
 public:
  Line(int startx, int endx, int starty, int endy, float lw);
  Line() {}
  void draw();
};

class Text {
private:
  int xpos;
  int ypos;
  string text;
public:
  Text(int xpos, int ypos, string text);
  Text() {}
  void draw();
};

class LegendItem {
/* TODO: upgrade the texts to use an array and dynamic memory */
private:
  Line line;
  Text t1, t2, t3;
  char numTexts = 0;
public:
  LegendItem(int startx, int endx, int starty, int endy, float lw,
                         const Text &t1, const Text &t2, const Text &t3);
  LegendItem(int startx, int endx, int starty, int endy, float lw,
                         const Text &t1, const Text &t2);
  LegendItem(int startx, int endx, int starty, int endy, float lw,
                         const Text &t1);
  void draw();
};

#endif
