#ifndef _DRAWFUNCS_
#define _DRAWFUNCS_

#include <string>
using namespace std;

void drawBox(double x, double y, double width, double height, float a, float b, float c);
void drawText(int x, int y, string text);
void drawBox(double x, double y, double width, double height);
void drawBox(int *pos);
void exitAll();
#endif
