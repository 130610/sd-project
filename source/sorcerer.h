#ifndef _SORCERER_
#define _SORCERER_

#include "ColorPoint2.h"
#include "physics.h"

class Sorcerer {
private:
  Point2d posn;
  bool movingRight;
  Hitbox* hitbox;

public:
  Sorcerer(unsigned numTargets);
  ~Sorcerer() { delete hitbox; }

  void turnAround() { movingRight = !movingRight; }
  void move();
  void draw(int offset);
  bool isHit();
};

#endif
