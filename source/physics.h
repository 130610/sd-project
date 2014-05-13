#ifndef _PHYSICSFUNCS_
#define _PHYSICSFUNCS_

#include <iostream>
#include "ColorPoint2.h"
using namespace std;

class Velocity
{
	bool gravity;
public:
	double velX;
	double velY;
	Velocity(): gravity(false), velX(0), velY(0) {};
	void set(Point2d start, Point2d end);//, double time);
	void move(Point2d &p);
	void applyGravity(double meter);
	void friction(double factor);
	void show() { cout << "velx: " << velX << "   vely: " << velY << endl; }
	void toggleGravity(bool g) { gravity = g; }
};

class Hitbox
{
public:
	Point2 pos;
	int width;
	int height;
	Hitbox(int x, int y, int w, int h): pos(x, y), width(w), height(h) {}
	void display() { pos.display(); }
	bool detect(Point2 &p, int w, int h);
	void setPosn(Point2 p) { pos = p; }
};

#endif
