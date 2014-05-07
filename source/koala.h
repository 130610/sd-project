#ifndef _KOALA_
#define _KOALA_

class Koala {
private:
  int x, y; // location of upper-left corner
  bool atBottom; // true at start, false after (if false, bottom is water)
  int texture;

public:
  int targetx, targety; // location we're moving the koala towards
  Koala();

  int getX() { return x; }
  int getY() { return y; }
  int getCtrX() { return x+40; } // visual center of koala for
  int getCtrY() { return y-40; } // trajectory display, etc.
  bool isAtBottom() { return atBottom; }
  bool isAtTarget();

  void loadTexture(int texture) { this->texture = texture; }

  void leaveBottom() { atBottom = false; }
  void setTarget(int newX, int newY) { targetx = newX; targety = newY; }
  void approachTarget();
  void scrollKoalaUp();
  void scrollKoalaDown();

  void drawTrajectory(int mouseposx, int mouseposy);
  void drawKoala(int mouseposx);
};

#endif
