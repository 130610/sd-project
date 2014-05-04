#include "InstructionLines.h"

Line::Line(int startx, int endx, int starty, int endy, float lw)
{
  xstart = startx;
  xend = endx;
  ystart = starty;
  yend = endy;
  z=0;
  lineWidth = lw;
}

void Line::draw()
{
  glBegin(GL_LINES);
  glLineWidth(lineWidth);
  glColor3f(1,0,1);
  glVertex3f(xstart,ystart,z);
  glVertex3f(xend,yend, z);
  glEnd();
}


Text::Text(int xpos, int ypos, string text)
{
  this->xpos = xpos;
  this->ypos = ypos;
  this->text = text;
}

void Text::draw()
{
  glColor3f(1,1,1);
  drawText(xpos, ypos, text);
}


LegendItem::LegendItem(int startx, int endx, int starty, int endy, float lw,
    const Text &t1, const Text &t2, const Text &t3)
{
  line = Line(startx, endx, starty, endy, lw);
  this->t1 = t1;
  this->t2 = t2;
  this->t3 = t3;
  numTexts = 3;
}

LegendItem::LegendItem(int startx, int endx, int starty, int endy, float lw,
    const Text &t1, const Text &t2)
{
  line = Line(startx, endx, starty, endy, lw);
  this->t1 = t1;
  this->t2 = t2;
  numTexts = 2;
}

LegendItem::LegendItem(int startx, int endx, int starty, int endy, float lw,
    const Text &t1)
{
  line = Line(startx, endx, starty, endy, lw);
  this->t1 = t1;
  numTexts = 1;
}

void LegendItem::draw() {
  if (numTexts >= 1)
    t1.draw();
  if (numTexts >= 2)
    t2.draw();
  if (numTexts >= 3)
    t3.draw();
  line.draw();
}


