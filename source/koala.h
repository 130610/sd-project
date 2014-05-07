#ifndef _KOALA_
#define _KOALA_

#include "ColorPoint2.h"

class Koala {
private:
  Point2 posn; // location of upper-left corner
  Point2 target; // location we're moving the koala towards
  bool atBottom; // true at start, false after (if false, bottom is water)
  int texture;

public:
  Koala();

  int getX() { return posn.x; }
  int getY() { return posn.y; }
  int getCtrX() { return posn.x+40; } // visual center of koala for
  int getCtrY() { return posn.y-40; } // trajectory display, etc.
  bool isAtBottom() { return atBottom; }
  bool isAtTarget() { return !(posn == target); } // why is this '!'?

  void loadTexture(int texture) { this->texture = texture; }

  void leaveBottom() { atBottom = false; }
  void setTarget(int x, int y) { target.x = x; target.y = y; }
  void approachTarget();
  void scrollKoalaUp();
  void scrollKoalaDown();

  void drawTrajectory(int mouseposx, int mouseposy);
  void drawKoala(int mouseposx);
};

#endif
