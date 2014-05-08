#ifndef _TEXT_
#define _TEXT_
#include <GL/glut.h>
#include <string.h>
#include "ColorPoint2.h"
#include "globaldefs.h"
#include "draw.h"

void drawBitmapText(char *string,float x,float y,float z);
void drawStrokeText(char*string,int x,int y,int z);
void drawWhiteText(float x, float y, const char *text);
void drawWhiteText(float x, float y, string text);




class textBox
{

  bool overTextBox;
  string textInBox;
  int textBox1[4];
  int textBox2[4];
 public:
  const unsigned int MAX_NUM_CHARS_IN_TEXTBOX =100;
  textBox(bool a, int c[], int d[]) 
    {
      overTextBox = a;
      textInBox = "";
      for(int i=0; i<4; i++)
	{
	  textBox1[i]=c[i];
	  textBox2[i]=d[i];
	}
    }

  bool onTextBox(int x, int y)
  {
  return x >= textBox1[0] && y >= textBox1[1] &&
         x <= textBox1[0]+textBox1[2] &&
         y <= textBox1[1]+textBox1[3];
  }

  bool getoverTextBox()
  {
    return overTextBox;
  }
  string getTextInBox()
  {
    return textInBox;
  }
 
  void changeTextInBox()
  {
    textInBox = "";
  }
  const unsigned int getmax_num_chars_in_textbox()
  {
    return MAX_NUM_CHARS_IN_TEXTBOX;
  }
  void changeoverTextBox(bool a)
  {
    overTextBox = a;
  }
 
  void drawTextBox()
  {
    glColor3f(.25, .25, .25);  // dark gray
    drawBox(textBox1);
    if (overTextBox) glColor3f(1,1,1);  // white
    else glColor3f(.75, .75, .75);  // light gray
    drawBox(textBox2);
    glColor3f(0, 0, 0);
  }
  void writeTextinBox()
  {
    if(overTextBox)
      {
	string withCursor(textInBox);
	withCursor +='|';
	glColor3f(0,0,0);
	drawText(textBox2[0]+5, textBox2[1]+ textBox2[3]-20, withCursor);
      }
    else
      {
	glColor3f(0,0,0);
	drawText(textBox2[0]+5, textBox2[1]+textBox2[3]-20, textInBox);
      }
  }


  void keyboardfunction(unsigned char c, int x, int y)
  {
    if(overTextBox)
      {
#ifdef DEBUG
	if(13==c){
	  cout<<"The text in box is: "<<textInBox<<endl;
	  textInBox="";
	}
#endif
	if('\b'==c || 127==c){
	  cerr<<"Does this happen!"<<endl;
	  if(textInBox.length()>=1) textInBox.erase(textInBox.end()-1);
	}else if ( c >= 32 && c <= 126 ) { // check for printable character
      // check that we don't overflow the box
      if (textInBox.length() < MAX_NUM_CHARS_IN_TEXTBOX ) textInBox += c;
	}
      }  
  }

};

#endif
