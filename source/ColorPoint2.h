#ifndef __COLORPT__
#define __COLORPT__
#include <iostream>
using namespace std;

struct Color {
  float red;
  float green;
  float blue;

  Color(float r, float g, float b) { red = r; green = g; blue = b; }
  Color() { red = 1; green = 1; blue = 1; }
  void display() { cout << red << ' ' << green << ' ' << blue << "  "; }
};

struct Point2d {
  double x;
  double y;
  void display() { cout << x << ' ' << y << "  "; }
  bool operator== (Point2d p) { return (x==p.x && y==p.y); }
  Point2d(double posx, double posy): x(posx), y(posy) {}
  Point2d() {}
};

struct Point2 {
  int x;
  int y;
  void display() { cout << x << ' ' << y << "  "; }
  bool operator== (Point2 p) { return (x==p.x && y==p.y); }
  Point2(int posx, int posy): x(posx), y(posy) {}
  Point2() {}
  Point2(const Point2d &p) { x = (int)p.x; y = (int)p.y; }
};

int distance(int x, int y, Point2 p);

#endif //__COLORPT__
