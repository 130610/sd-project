#ifndef _KOALA_
#define _KOALA_

#include "physics.h"
#include "ColorPoint2.h"

class Koala {
private:
  //Point2 target; // location we're moving the koala towards
  bool atBottom; // true at start, false after (if false, bottom is water)
  int texture;

public:
  Velocity vel;
  Point2d posn; // location of upper-left corner
  bool jumps;

  Koala();

  int getX() { return (int) posn.x; }
  int getY() { return (int) posn.y; }
  int getCtrX() { return (int) posn.x+40; } // visual center of koala for
  int getCtrY() { return (int) posn.y-40; } // trajectory display, etc.
  bool isAtBottom() { return atBottom; }
  void makeAtBottom() { atBottom = true; }
  //bool isAtTarget() { return !(posn == target); } // why is this '!'?

  void loadTexture(int texture) { this->texture = texture; }

  void leaveBottom() { atBottom = false; }
  void setTarget(Point2d target/*, int frames*/) { vel.set(posn, target/*, frames*/); }
  void setPosition(int x, int y/*, int frames*/) { posn.x = x; posn.y = y; }
  void approachTarget();
  void move();
  void velocityZero() { vel.set(posn, posn); }
  void velocityReverse() { vel.velX -= 2 * vel.velX; vel.velY -= 2 * vel.velY; }
  void scrollKoalaUp();
  void scrollKoalaDown();

  void drawTrajectory(int mouseposx, int mouseposy);
  void drawKoala(int mouseposx);
};

#endif
