#include "sorcerer.h"
#include "target.h"
#include "physics.h"
#include "draw.h"

const int SORCERER_ABOVE_BOXES = 300;
const int SORCERER_START_X = 200;

Sorcerer::Sorcerer(unsigned numTargets)
{
  posn.x = SORCERER_START_X;
  movingRight = true;
  posn.y = MAX_Y_FACTOR * (numTargets); // const defined in target.h
  hitbox = new Hitbox(posn.x, posn.y, 100, 100);
  cerr << posn.x << " " << posn.y << endl;
}

void Sorcerer::draw(int offset)
{
  drawBox(posn.x, posn.y + offset + SORCERER_ABOVE_BOXES,
          100, 100, 0,1,0);
}
