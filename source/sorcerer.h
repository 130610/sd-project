#ifndef _SORCERER_
#define _SORCERER_

#include "ColorPoint2.h"
#include "physics.h"

class Sorcerer {
private:
  bool movingRight;
  int sorcererTexture;

public:
  bool isMoving;
  Hitbox* hitbox;
  Point2 posn;
  Sorcerer(unsigned numTargets);
  ~Sorcerer() { delete hitbox; }

  void turnAround() { movingRight = !movingRight; }
  void move();
  void draw(int offset);
  bool isHit(Point2d &pos, int w, int h, int offset);
};

#endif
