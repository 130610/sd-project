#ifndef _TARGET_
#define _TARGET_

#include <string>
#include <vector>
using namespace std;

#define MAX_X_FACTOR 200
#define MAX_Y_FACTOR 500
#define BOX_WIDTH 150
#define BOX_HEIGHT 250

class Target
{
	string targetName;
	Target **children;
	Target **parents;
	int posX;
	int posY;
	int numParents;
	int numChildren;


public:
	bool posInited;
	Target(): targetName(""), children(0), parents(0),  numParents(0), numChildren(0), posInited(0) {}
	Target(string n): targetName(n), children(0), parents(0), numParents(0), numChildren(0), posInited(0) {}
	Target(string n, Target *p);

	~Target();

	void addChildren(string dl, Target **r);
	void addParent(Target *p);
	void setName(string n) { targetName = n; }
	string getName() { return targetName; }
	int getPosY() { return posX; }
	int getPosX() { return posY; }
	Target* findTarget(string n);
	void initPositions(int d = 0, int ind = 0);
	void drawTargetBoxes(int offset);
	void drawDependLines();
	void printTree();
};

//class SplitString : public string {
//	vector<string> flds;
//public:
//	SplitString(string s) : string(s) { };
//	vector<string>& split(char delim);
//};

Target **parseTargets(const char *filename);
vector<string> splitString(string s, char d);
void addLine(string *&ll, char *l);
int getLineListSize(string *ll);
bool matchTargetLine(string l, string& n, string& d);
void addTarget(Target** r, string n, string d);

#endif
