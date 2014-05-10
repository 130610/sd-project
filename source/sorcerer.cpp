#include "sorcerer.h"
#include "target.h"
#include "physics.h"
#include "draw.h"
#include "globaldefs.h"

const int SORCERER_ABOVE_BOXES = 400; // distance above last makefile box range
const int SORCERER_START_X = 200; // where sorcerer begins across screen
const int SORCERER_WIDTH = 100;
const int SORCERER_HEIGHT = 100;
const int SORCERER_MOVE_RATE = 10; // number of pixels moved on each move call

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
          SORCERER_WIDTH, SORCERER_HEIGHT, 0,1,0);
}

void Sorcerer::move()
{
  if (movingRight)
    posn.x += SORCERER_MOVE_RATE;
  else
    posn.x -= SORCERER_MOVE_RATE;

  hitbox->setPosn(posn);
  if ( (posn.x > WIDTH - SORCERER_WIDTH - 5) || (posn.x < 5) )
    turnAround();
}

bool Sorcerer::isHit(Point2d &koalaPosn, int w, int h, int offset)
{
  Point2 tmppos(koalaPosn.x, koalaPosn.y - offset - 400);
  bool ret = hitbox->detect(tmppos, w, h);
	koalaPosn.x = tmppos.x; koalaPosn.y = tmppos.y + offset + 400;
  return ret;
}
