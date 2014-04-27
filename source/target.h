#ifndef _TARGET_
#define _TARGET_

#include <string>
using namespace std;

class Target
{
	string targetName;
	Target **children;
	Target **parents;
	int posX;
	int posY;

public:
	Target(): targetName(""), children(0), parents(0), posX(0), posY(0) {}
	Target(const char *n): targetName(n), children(0), parents(0), posX(0), posY(0) {}
};

Target *parseTargets(const char *filename);
void addLine(string *&ll, char *l);
int getLineListSize(string *ll);

#endif
