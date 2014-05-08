#ifdef MACOSX
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <math.h>
#include <iostream>
using namespace std;

#include "globaldefs.h"
#include "koala.h"
#include "texture.h"

Koala::Koala()
{
  posn.x = 10, posn.y = 120;
  atBottom = true;
}

void Koala::move()
{
	vel.move(posn);
}

//void Koala::approachTarget()
//{
//  posn.x += (target.x - posn.x) / 15;
//  posn.y += (target.y - posn.y) / 15;
//}

void Koala::scrollKoalaUp()
{
//  target.y += HEIGHT - 200 - posn.y;
  posn.y = HEIGHT - 200;
}

void Koala::scrollKoalaDown()
{
//  target.y += 100 - posn.y;
  posn.y = 100;
}

void Koala::drawTrajectory(int mouseposx, int mouseposy)
{
  /* not yet implemented -- see also some code removed in
   * 5bdf728d5fa4cff5eccdabd27f18cc06a9df895f
  int hypotenuse = sqrt(((mouseposx-getCtrX())*(mouseposx-getCtrX())) +
                        ((mouseposy-getCtrY())*(mouseposy-getCtrY())));

  if(hypotenuse > 100)
    hypotenuse = 100;
  */
  
  glColor3f(1,1,1);
    glLineStipple(1, 0xAAAA);
    glEnable(GL_LINE_STIPPLE);
    glBegin(GL_LINES);
    glVertex3f(getCtrX(), getCtrY(), 0);
    glVertex3f(getCtrX()+(mouseposx-getCtrX()), getCtrY()+(mouseposy-getCtrY()), 0);
  glEnd();
}

void Koala::drawKoala(int mouseposx)
{
  if(mouseposx > posn.x)
    drawTexture(texture,posn.x,posn.y,100,-100);
  else
    drawTexture(texture, posn.x, posn.y, 100,-100, 1.0,M_PI);
}
