#ifndef _KOALA_
#define _KOALA_

#include "physics.h"
#include "ColorPoint2.h"

class Animal{
 protected:
  bool atBottom;
  int texture;

public:
  Point2d posn; // location of upper-left corner
  Velocity vel;
  bool jumps;

  Animal();
  int getX(){ return (int)posn.x;}
  int getY() { return (int) posn.y; }
  Point2d getPosn() { return posn; }
  int getCtrX() { return (int) posn.x+40; } // visual center of koala for
  int getCtrY() { return (int) posn.y-40; } // trajectory display, etc.
  bool isAtBottom() { return atBottom; }
  void makeAtBottom() { atBottom = true; }
  //bool isAtTarget() { return !(posn == target); } // why is this '!'?

  virtual void loadTexture(int texture) { this->texture = texture; }

  void leaveBottom() { atBottom = false; }
  void setTarget(Point2d target/*, int frames*/) { vel.set(posn, target/*, frames*/); }
  void setPosition(int x, int y/*, int frames*/) { posn.x = x; posn.y = y; }
  void approachTarget();
  void move();
  void velocityZero() { vel.set(posn, posn); }
  void velocityReverse() { vel.velX -= 2 * vel.velX; vel.velY -= 2 * vel.velY; }
  void scrollAnimalUp();
  void scrollAnimalDown();
  virtual void drawTrajectory(int mouseposx, int mouseposy)=0;

  
};

class Koala:public Animal{
 public:
  //Koala();
  void loadTexture(int texture) { this->texture = texture; }
  void drawKoala(int mouseposx);
  void drawTrajectory(int mouseposx, int mouseposy);

};

class Jaguar:public Animal {
 public:
  void loadTexture(int texture){ this -> texture = texture;}
  void drawJaguar(int mouseposx);
  void drawTrajectory(int mouseposx, int mouseposy);
};

class FlyingSquirrel:public Animal {
 public:
  void loadTexture(int texture){ this -> texture = texture;}
  void drawflyingSquirrel(int mouseposx);
  void drawTrajectory(int mouseposx, int mouseposy);
};

class Swan:public Animal{
 public:
  void loadTexture(int texture) { this -> texture = texture; }
  void drawSwan(int mouseposx);
  void drawTrajectory(int mouseposx, int mouseposy);
};

class SeaTurtle:public Animal{
 public:
  void loadTexture(int texture) { this -> texture = texture; }
  void drawseaTurtle(int mouseposx);
  void drawTrajectory(int mouseposx, int mouseposy);
};

#endif
