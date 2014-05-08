#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <time.h>
#include "target.h"
#include "draw.h"
#include "physics.h"
#ifdef MACOSX
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
using namespace std;

int numRoots = 1;
int seed = (int) time(NULL);

Target::Target(string n, Target *p): targetName(n), children(0), numParents(0), numChildren(0), posInited(0)
{
	parents = new Target*[1];
	parents[0] = p;
}

Target::~Target()
{
	if (parents) delete [] parents;
	if (children) delete [] children;
}

void Target::addChildren(string dl, Target **r)
{
	Target **tmpList;
	vector<string> dependsList = splitString(dl, ' ');
	tmpList = new Target*[numChildren + dependsList.size()];

	for (int i = 0; i < numChildren; i++) {
		tmpList[i] = children[i];
	}
	for (unsigned i = 0; i < dependsList.size(); i++) for (int j = 0; j < numRoots; j++) {
		if (r[j]->findTarget(dependsList[i])) {
			tmpList[i + numChildren] = r[j]->findTarget(dependsList[i]);
			tmpList[i + numChildren]->addParent(this);
		} else {
			tmpList[i + numChildren] = new Target(dependsList[i], this);
		}
	}
	numChildren +=dependsList.size();

	delete [] children;
	children = tmpList;
}

void Target::addParent(Target *p)
{
	Target **tmpList = new Target*[numParents + 1];
	for (int i = 0; i < numParents; i++) {
		tmpList[i] = parents[i];
	}
	tmpList[numParents++] = p;
	if (parents) delete [] parents;
	parents = tmpList;
}

void Target::drawTargetBoxes(int offset)
{
	for (int i = 0; i < numChildren; i++) {
		children[i]->drawTargetBoxes(offset);
	}

	drawBox(pos.x, pos.y + offset, BOX_WIDTH, BOX_HEIGHT, 1, 1, 1);
	drawText(pos.x + 3, pos.y + 3+offset, targetName);

}

void Target::drawDependLines()
{
	for (int i = 0; i < numChildren; i++) {
		children[i]->drawDependLines();
		glBegin(GL_LINES);
			glVertex3f(pos.x, pos.y, 0);
			glVertex3f(children[i]->getPosX(), children[i]->getPosY(), 0);
		glEnd();
	}
}

void Target::printTree()
{
	cout << this->getName() << "(" << getPosX()  << ", " << getPosY() << ")" << " depends on " ;
	cout << children[0]->getName() << "(" << children[0]->getPosX()  << ", " << children[0]->getPosY() << ")";
	for (int i = 1; i < numChildren; i++) {
		cout << " and " << children[i]->getName() << "(" << children[i]->getPosX()  << ", " << children[i]->getPosY() << ")";
	}
	cout << endl;
}

// does a depth first search for at target with name n starting at the root
// target r
Target *Target::findTarget(string n)
{
	if (targetName == n) return this;

	for (int i = 0; i < numChildren; i++) {
		if (children[i]->findTarget(n)) return children[i]->findTarget(n);
	}

	return 0;
}

// initializes the positions of a target and all of its children based on their
// depth d in the tree, and their index ind in children with their same depth
void Target::initPositions(int d, int ind)
{
	for (int i = 0; i < numChildren; i++) {
		children[i]->initPositions(d + 1, i + ind);
	}

	if (!posInited) {
		srand(seed++);
		pos.x = (ind * MAX_X_FACTOR) + (rand() % MAX_X_FACTOR);
		srand(seed++);
		pos.y = (d * MAX_Y_FACTOR) + (rand() % MAX_Y_FACTOR);
		hitbox = new Hitbox(pos, BOX_WIDTH, BOX_HEIGHT);
		posInited = true;
	}
}

vector<string> splitString(string s, char d)
{
	vector<string> flds;
	string buf = "";
	for (unsigned i = 0; i < s.length(); i++) {
		if (s[i] != d) {
			buf += s[i];
		} else if (buf.length() > 0) {
			flds.push_back(buf);
			buf = "";
		}
	}
	if (!buf.empty()) {
		flds.push_back(buf);
	}
	return flds;
}

Target **parseTargets(const char *filename)
{
	Target **root = new Target *[1];
	string *lineList = new string[1]; 
	char line[128];
	char c;
	int i = 0;
	int numTargets = 0;
	ifstream ifs(filename);
	string tName, tDepends;

	while (ifs.get(c)) {
		line[i++] = c;
		if (c == '\n') {
			line[i] = '\0';
			addLine(lineList, line);
			i = 0;
		}
	}

	for (int i = 0; i < getLineListSize(lineList); i++) {
		if (matchTargetLine(lineList[i], tName, tDepends) && numTargets == 0) {
			root[0] = new Target(tName);
			root[0]->addChildren(tDepends, root);
			numTargets++;
		} else if (matchTargetLine(lineList[i], tName, tDepends)) {
			addTarget(root, tName, tDepends);
			numTargets++;
		}
	}
	return root;
}

void addLine(string *&ll, char *l)
{
	string *tmpList;
	int len = getLineListSize(ll);

	tmpList = new string[len + 1];

	for (int i = 0; i < len; i++) {
		tmpList[i] = ll[i];
	}
	if (l[0]) tmpList[len - 1] = l;
	tmpList[len] = "";

	delete [] ll;
	ll = tmpList;
}

int getLineListSize(string *ll)
{
	int len = 0;
	while (ll[len++] != "");
	return len;
}

// reads a string s, and returns whether it is the declaration of a rule in a
// makefile; reads the rule into the string n, and the dependencies into d
bool matchTargetLine(string l, string& n, string& d)
{
	unsigned i = 0;
	bool inName = true;
	n = d = "";

	if (l[0] == '\t' || l[0] == '\n') {
		return false;
	}
	if (l.empty()) {
		return false;
	}
	while (l[i] != '\n' && i < l.length()) {
		if (l[i] == ':'){
			inName = false;
		} else if (inName) {
			n.append(1, l[i]);
		} else if (!inName) {
			d.append(1, l[i]);
		}
		i++;
	}
	return true;
}

void addTarget(Target **r, string n, string d)
{
	Target **tmpRoot;
	bool exists = false;
	for (int i = 0; i < numRoots; i++) {
		if (r[i]->findTarget(n)) {
			r[i]->findTarget(n)->addChildren(d, r);
			exists = true;
			break;
		}
	}
	if (!exists) {
		tmpRoot = new Target *[numRoots + 1];
		for (int i = 0; i < numRoots; i++) {
			tmpRoot[i] = r[i];
		}
		tmpRoot[numRoots + 1] = new Target(n);
		tmpRoot[numRoots + 1]->addChildren(d, r);
		numRoots++;
	}
}
