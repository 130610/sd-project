#ifndef _TARGET_
#define _TARGET_

#include <string>
#include <vector>
#include "physics.h"
using namespace std;

#define MAX_X_FACTOR 400
#define MAX_Y_FACTOR 500
#define BOX_WIDTH 150
#define BOX_HEIGHT 250

class Target
{
	string targetName;
	Target **children;
	Target **parents;
	int numParents;
	int numChildren;
	Point2 pos;
	Hitbox *hitbox;

public:
	/* constructors */
	bool posInited;
	Target(): targetName(""), children(0), parents(0),  numParents(0), numChildren(0), posInited(0) {}
	Target(string n): targetName(n), children(0), parents(0), numParents(0), numChildren(0), posInited(0) {}
	Target(string n, Target *p);

	/* destructor */
	~Target();

	/* methods */
	void addChildren(string dl, Target **r);
	void addParent(Target *p);
	void setName(string n) { targetName = n; }
	string getName() { return targetName; }
	int getPosY() { return pos.x; }
	int getPosX() { return pos.y; }
	Target* findTarget(string n);
	void initPositions(int d = 0, int ind = 0);
	void drawTargetBoxes(int offset);
	bool checkCollisions(Point2d &pos, int w, int h, int offset);
	void drawDependLines();
	void printTree();
  unsigned getNumTargets(unsigned level=0);
};

/* other functions */
Target **parseTargets(const char *filename);
vector<string> splitString(string s, char d);
void addLine(string *&ll, char *l);
int getLineListSize(string *ll);
bool matchTargetLine(string l, string& n, string& d);
void addTarget(Target** r, string n, string d);

#endif
