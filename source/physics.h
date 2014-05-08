#ifndef _PHYSICSFUNCS_
#define _PHYSICSFUNCS_

#include <iostream>
#include "ColorPoint2.h"
using namespace std;

class Velocity
{
	int velX;
	int velY;
public:
	Velocity(): velX(0), velY(0) {};
	void set(Point2 start, Point2 end, double time);
	void move(Point2 &p);
	void gravity(int meter);
	void show() { cout << "velx: " << velX << "   vely: " << velY << endl; }
};

class Hitbox
{
	Point2 pos;
	int width;
	int height;
public:
	Hitbox(int x, int y, int w, int h): width(w), height(h) { pos.x = x; pos.y = y; }
	bool detect(Point2 &p, int w, int h);
};

#endif
