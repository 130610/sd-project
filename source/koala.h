#ifndef _KOALA_
#define _KOALA_

class Koala {
private:
  int x, y; // location of upper-left corner
  int targetx, targety; // location we're moving the koala towards
  bool atTarget; // if false, no need to move the koala
  bool atBottom; // true at start, false after (if false, bottom is water)
  int texture;

public:
  Koala();

  int getX() { return x; }
  int getY() { return y; }
  int getCtrX() { return x+40; } // visual center of koala for
  int getCtrY() { return y-40; } // trajectory display, etc.
  void setTarget(int newX, int newY) { targetx = newX; targety = newY; }
  void scrollKoalaUp();
  void scrollKoalaDown();

  void drawTrajectory(int mouseposx, int mouseposy);
  void drawKoala(int mouseposx);
};

#endif
