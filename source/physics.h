#ifndef _PHYSICSFUNCS_
#define _PHYSICSFUNCS_

#include <iostream>
#include "ColorPoint2.h"
using namespace std;

class Velocity
{
	double velX;
	double velY;
public:
	Velocity(): velX(0), velY(0) {};
	void set(Point2d start, Point2d end);//, double time);
	void move(Point2d &p);
	void gravity(double meter);
	void friction(double factor);
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
