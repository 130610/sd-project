#ifndef _KOALA_
#define _KOALA_

#include "physics.h"
#include "ColorPoint2.h"

class Koala {
private:
  Point2d posn; // location of upper-left corner
  //Point2 target; // location we're moving the koala towards
  bool atBottom; // true at start, false after (if false, bottom is water)
  int texture;
  Velocity vel;

public:
  Koala();

  int getX() { return (int) posn.x; }
  int getY() { return (int) posn.y; }
  int getCtrX() { return (int) posn.x+40; } // visual center of koala for
  int getCtrY() { return (int) posn.y-40; } // trajectory display, etc.
  bool isAtBottom() { return atBottom; }
  //bool isAtTarget() { return !(posn == target); } // why is this '!'?

  void loadTexture(int texture) { this->texture = texture; }

  void leaveBottom() { atBottom = false; }
  void setTarget(Point2d target/*, int frames*/) { vel.set(posn, target/*, frames*/); }
  void approachTarget();
  void move();
  void scrollKoalaUp();
  void scrollKoalaDown();

  void drawTrajectory(int mouseposx, int mouseposy);
  void drawKoala(int mouseposx);
};

#endif
