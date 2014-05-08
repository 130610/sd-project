#ifdef MACOSX
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <string>
#include <string.h>

#include "text.h"

using namespace std;

textBox::textBox(bool a, int c[], int d[])
{
  overTextBox = a;
  textInBox = "";
  for(int i=0; i<4; i++) {
    textBox1[i]=c[i];
    textBox2[i]=d[i];
  }
}

bool textBox::onTextBox(int x, int y)
{
  return x >= textBox1[0] && y >= textBox1[1] &&
      x <= textBox1[0]+textBox1[2] &&
      y <= textBox1[1]+textBox1[3];
}

void textBox::drawTextBox()
{
  glColor3f(.25, .25, .25);  // dark gray
  drawBox(textBox1);
  if (overTextBox) glColor3f(1,1,1);  // white
  else glColor3f(.75, .75, .75);  // light gray
  drawBox(textBox2);
  glColor3f(0, 0, 0);
}

void textBox::writeTextinBox()
{
  if(overTextBox) {
    string withCursor(textInBox);
    withCursor +='|';
    glColor3f(0,0,0);
    drawText(textBox2[0]+5, textBox2[1]+ textBox2[3]-20, withCursor);
  } else {
    glColor3f(0,0,0);
    drawText(textBox2[0]+5, textBox2[1]+textBox2[3]-20, textInBox);
  }
}

void textBox::keyboardfunction(unsigned char c, int x, int y)
{
  if(overTextBox) {
#ifdef DEBUG
    if(13==c) {
      cout<<"The text in box is: "<<textInBox<<endl;
      textInBox="";
    } else
#endif
           if('\b'==c || 127==c) {
      if (textInBox.length()>=1)
        textInBox.erase( textInBox.end()-1 );

    } else if ( c >= 32 && c <= 126 ) {
      // printable characters; don't overflow the box
      if (textInBox.length() < MAX_NUM_CHARS_IN_TEXTBOX )
        textInBox += c;
    }
  }  
}

/* Source for the following functions:
 * http://stackoverflow.com/questions/11190205/opengl-display-animation-and-draw-text
 */

void drawBitmapText(char *string,float x,float y,float z)
{
  char *c;
  glRasterPos3f(x, y,z);

  for (c=string; *c != '\0'; c++) {
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
  }
}

void drawStrokeText(char*string,int x,int y,int z)
{
  char *c;
  glPushMatrix();
  glTranslatef(x, y+8,z);
  glScalef(0.09f,-0.08f,z);

  for (c=string; *c != '\0'; c++)
  {
    glutStrokeCharacter(GLUT_STROKE_ROMAN , *c);
  }
  glPopMatrix();
}

void drawWhiteText(float x, float y, const char *text)
{
  glRasterPos2f(x,y);
  int length = strlen(text);
  for (int i=0; i<length; i++)
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
}

void drawWhiteText(float x, float y, string text)
{
  glRasterPos2f(x,y);
  int length = text.length();
  for (int i=0; i<length; i++)
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
}
