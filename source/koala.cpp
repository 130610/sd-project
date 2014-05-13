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

Animal::Animal()
{
  posn.x = 10, posn.y =200;
  atBottom = true;
  jumps =1;
}

void Animal::move()
{
	vel.move(posn);
}

//void Koala::approachTarget()
//{
//  posn.x += (target.x - posn.x) / 15;
//  posn.y += (target.y - posn.y) / 15;
//}

void Animal::scrollAnimalUp()
{
//  target.y += HEIGHT - 200 - posn.y;
  posn.y = HEIGHT - 200;
}

void Animal::scrollAnimalDown()
{
//  target.y += 100 - posn.y;
  posn.y = 200;
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
    glLineStipple(5, 0xAAAA);
    glEnable(GL_LINE_STIPPLE);
    glBegin(GL_LINES);
    glVertex3f(getCtrX(), getCtrY(), 0);
    glVertex3f(getCtrX()+(mouseposx-getCtrX())-54, getCtrY()+(mouseposy-getCtrY()), 0);
    glDisable(GL_LINE_STIPPLE);
  glEnd();
}

void Jaguar::drawTrajectory(int mouseposx, int mouseposy)
{
  glColor3f(1,1,1);
    glLineStipple(5, 0xAAAA);
    glEnable(GL_LINE_STIPPLE);
    glBegin(GL_LINES);
    glVertex3f(getCtrX(), getCtrY(), 0);
    glVertex3f(getCtrX()+(mouseposx-getCtrX()-54), getCtrY()+(mouseposy-getCtrY()), 0);
    glDisable(GL_LINE_STIPPLE);
  glEnd();
}

void FlyingSquirrel::drawTrajectory(int mouseposx, int mouseposy)
{
glColor3f(1,1,1);
    glLineStipple(5, 0xAAAA);
    glEnable(GL_LINE_STIPPLE);
    glBegin(GL_LINES);
    glVertex3f(getCtrX()+50, getCtrY(), 0);
    glVertex3f(getCtrX()+(mouseposx-getCtrX())-54, getCtrY()+(mouseposy-getCtrY()), 0);
    glDisable(GL_LINE_STIPPLE);
  glEnd();
}

void Swan::drawTrajectory(int mouseposx, int mouseposy)
{
glColor3f(1,1,1);
    glLineStipple(5, 0xAAAA);
    glEnable(GL_LINE_STIPPLE);
    glBegin(GL_LINES);
    glVertex3f(getCtrX()+20, getCtrY()-30, 0);
    glVertex3f(getCtrX()+(mouseposx-getCtrX())-54, getCtrY()+(mouseposy-getCtrY()), 0);
    glDisable(GL_LINE_STIPPLE);
  glEnd();
}

void SeaTurtle::drawTrajectory(int mouseposx, int mouseposy)
{
glColor3f(1,1,1);
    glLineStipple(5, 0xAAAA);
    glEnable(GL_LINE_STIPPLE);
    glBegin(GL_LINES);
    glVertex3f(getCtrX()+30, getCtrY()-20, 0);
    glVertex3f(getCtrX()+(mouseposx-getCtrX())-54, getCtrY()+(mouseposy-getCtrY()), 0);
    glDisable(GL_LINE_STIPPLE);
  glEnd();
}

void Koala::drawKoala(int mouseposx)
{
  if(mouseposx > posn.x)
    drawTexture(texture,posn.x,posn.y,100,-100);
  else
    drawTexture(texture, posn.x+100, posn.y, -100,-100, 1.0);
}

void Jaguar::drawJaguar(int mouseposx)
{
  if(mouseposx >posn.x)
    drawTexture(texture, posn.x-50, posn.y+50, 200, -100, 1.0, -3.14/2);
  else
    drawTexture(texture, posn.x+150, posn.y+50, -200, -100, 1.0, -3.14/2);
}

void FlyingSquirrel::drawflyingSquirrel(int mouseposx)
{
  if(mouseposx > posn.x)
    drawTexture(texture, posn.x-20, posn.y, 200,-100,1.0, 0);
  else
    drawTexture(texture, posn.x+180, posn.y, -200,-100,1.0, 0);
}

void Swan::drawSwan(int mouseposx)
{
  if(mouseposx>posn.x)
    drawTexture(texture, posn.x-40, posn.y-10, 200,-100,1.0,0);
  else
    drawTexture(texture, posn.x+150, posn.y-10, -200,-100,1.0,0);
}

void SeaTurtle::drawseaTurtle(int mouseposx)
{
  if(mouseposx > posn.x)
    drawTexture(texture, posn.x-30, posn.y, 200, -100,1.0,0);
  else
    drawTexture(texture, posn.x+150, posn.y, -200,-100,1.0,0);
}
