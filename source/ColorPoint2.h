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

struct Point2 {
  int x;
  int y;
  void display() { cout << x << ' ' << y << "  "; }
};

int distance(int x, int y, Point2 p);

#endif //__COLORPT__
