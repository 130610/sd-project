#ifndef _TEXT_
#define _TEXT_
#include <GL/glut.h>
#include <string.h>
#include "ColorPoint2.h"
#include "globaldefs.h"
#include "draw.h"

class textBox {
private:
  bool overTextBox;
  string textInBox;
  int textBox1[4];
  int textBox2[4];
  const unsigned int MAX_NUM_CHARS_IN_TEXTBOX = 100;

public:
  textBox(bool a, int c[], int d[]);

  bool onTextBox(int x, int y);
  bool getoverTextBox() { return overTextBox; }
  string getTextInBox() { return textInBox; }

  void erase() { textInBox = ""; }
  void changeoverTextBox(bool a) { overTextBox = a; }

  void drawTextBox();
  void writeTextinBox();
  void keyboardfunction(unsigned char c, int x, int y);

};

void drawBitmapText(char *string,float x,float y,float z);
void drawStrokeText(char*string,int x,int y,int z);
void drawWhiteText(float x, float y, const char *text);
void drawWhiteText(float x, float y, string text);

#endif
