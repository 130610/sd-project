#include "sorcerer.h"
#include "target.h"
#include "physics.h"
#include "draw.h"
#include "texture.h"
#include "globaldefs.h"

const int SORCERER_ABOVE_BOXES = 400; // distance above last makefile box range -- DO NOT CHANGE THIS or hitbox will be messed up for some reason I don't understand
const int SORCERER_START_X = 200; // where sorcerer begins across screen
const int SORCERER_WIDTH = 100;
const int SORCERER_HEIGHT = 161;
const int SORCERER_MOVE_RATE = 10; // number of pixels moved on each move call

Sorcerer::Sorcerer(unsigned numTargets)
{
  posn.x = SORCERER_START_X;
  movingRight = true;
  posn.y = (MAX_Y_FACTOR * (numTargets) + SORCERER_ABOVE_BOXES);
  hitbox = new Hitbox(posn.x, posn.y, SORCERER_WIDTH, SORCERER_HEIGHT);
#ifdef DEBUG
  cerr << posn.x << " " << posn.y << endl;
#endif
}

void Sorcerer::draw(int offset)
{
  /* this line for some odd reason doesn't work if it's anywhere else */
  sorcererTexture = loadTexture("../resources/gppsorcerer.pam");

  /* this draws the texture upside down, so make sure the texture is
   * upside down on disk */
  drawTexture(sorcererTexture, posn.x, (posn.y + offset + SORCERER_ABOVE_BOXES), SORCERER_WIDTH, SORCERER_HEIGHT);
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
  /* added above_boxes back in; not sure why it's necessary, but it works */
  Point2 tmppos(koalaPosn.x, koalaPosn.y - offset - SORCERER_ABOVE_BOXES);// - SORCERER_ABOVE_BOXES);
  bool ret = hitbox->detect(tmppos, w, h);
  koalaPosn.x = tmppos.x; koalaPosn.y = tmppos.y + offset + SORCERER_ABOVE_BOXES;// + SORCERER_ABOVE_BOXES;
  return ret;
}
