#include "sorcerer.h"
#include "target.h"
#include "physics.h"
#include "draw.h"
#include "globaldefs.h"

const int SORCERER_ABOVE_BOXES = 400; // distance above last makefile box range -- DO NOT CHANGE THIS or hitbox will be messed up for some reason I don't understand
const int SORCERER_START_X = 200; // where sorcerer begins across screen
const int SORCERER_WIDTH = 100;
const int SORCERER_HEIGHT = 100;
const int SORCERER_MOVE_RATE = 10; // number of pixels moved on each move call

Sorcerer::Sorcerer(unsigned numTargets)
{
  posn.x = SORCERER_START_X;
  movingRight = true;
  posn.y = (MAX_Y_FACTOR * (numTargets) + SORCERER_ABOVE_BOXES);
  hitbox = new Hitbox(posn.x, posn.y, SORCERER_WIDTH, SORCERER_HEIGHT);
  //cerr << posn.x << " " << posn.y << endl;
}

void Sorcerer::draw(int offset)
{
  drawBox(posn.x, posn.y + offset,// + SORCERER_ABOVE_BOXES,
          SORCERER_WIDTH, SORCERER_HEIGHT, 0,1,0);
}

void Sorcerer::move()
{
  if (movingRight)
    posn.x += SORCERER_MOVE_RATE;
  else
    posn.x -= SORCERER_MOVE_RATE;

  Point2 tmppos = posn;
  tmppos.y += SORCERER_HEIGHT;
  hitbox->setPosn(tmppos);
  if ( (posn.x > WIDTH - SORCERER_WIDTH - 5) || (posn.x < 5) )
    turnAround();
}

bool Sorcerer::isHit(Point2d &koalaPosn, int w, int h, int offset)
{
  Point2 tmppos(koalaPosn.x, koalaPosn.y - offset);// - SORCERER_ABOVE_BOXES);
  bool ret = hitbox->detect(tmppos, w, h);
  koalaPosn.x = tmppos.x; koalaPosn.y = tmppos.y + offset;// + SORCERER_ABOVE_BOXES;
  return ret;
}
