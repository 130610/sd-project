#ifndef _InstructionLines_
#define _InstructionLines_
#include <iostream>
using namespace std;
#include <GL/glut.h>
#include <string.h>
#include "ColorPoint2.h"
#include "globaldefs.h"

#include <iostream>
#include <iomanip>
#include <math.h>
#include <sstream>
#include <stdlib.h>
#include <vector>
#include <sys/time.h>

#ifdef MACOSX
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
class Lines{
  float xstart;
  float xend;
  float ystart;
  float yend;
  float z;
  float lineWidth;
 public:
  Lines(float startx, float endx, float starty, float endy, float lw)
   {
     xstart = startx;
     xend = endx;
     ystart = starty;
     yend = endy;
     z=0;
     lineWidth = lw;
   }
  void drawLines()
  {
    glBegin(GL_Lines);
    glLineWidth(lineWidth);
    glColor3f(1,0,1);
    glVertex3f(xstart,ystart,z);
    glVertex3f(xend,yend, z);
    glEnd();
  }

};

#endif
