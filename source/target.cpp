#include <iostream>
#include <fstream>
#include <string>
#include "target.h"
using namespace std;

int numRoots = 1;

Target::Target(string n, Target *p): targetName(n), children(0), posX(0), posY(0), numParents(0), numChildren(0)
{
	parents = new Target*[1];
	parents[0] = p;
}

void Target::addChildren(string dl)
{
	Target **tmpList;
	vector<string> dependsList = splitString(dl, ' ');
	tmpList = new Target*[numChildren + dependsList.size()];

	for (int i = 0; i < numChildren; i++) {
		tmpList[i] = children[i];
	}
	for (unsigned i = 0; i < dependsList.size(); i++) {
		tmpList[i + numChildren] = new Target(dependsList[i], this);
	}
	numChildren +=dependsList.size();

	delete [] children;
	children = tmpList;
}

void Target::printTree()
{
	cout << this->getName() << " depends on " ;
	cout << children[0]->getName() << "(" << children[0]->getPosX()  << ", " << children[0]->getPosY() << ")";
	for (int i = 1; i < numChildren; i++) {
		cout << " and " << children[i]->getName() << "(" << children[0]->getPosX()  << ", " << children[0]->getPosY() << ")";
	}
	cout << endl;
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

Target *parseTargets(const char *filename)
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
//			cout << "made root" << endl;
			root[0]->addChildren(tDepends);
//			cout << "added children" << endl;
			numTargets++;
//			cout << "made root at line " << i + 1 << endl;
		} else if (matchTargetLine(lineList[i], tName, tDepends)) {
//			cout << "found target at line " << i + 1 << endl;
			addTarget(root, tName, tDepends);
			numTargets++;
		}
	}
//	cout << root[0]->findTarget("cat")->getName();
	return root[0];
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
	posX = d;
	posY = ind;

	for (int i = 0; i < numChildren; i++) {
		children[i]->initPositions(d + 1, i + ind);
	}
}

void addTarget(Target **r, string n, string d)
{
	Target **tmpRoot;
	bool exists = false;
	for (int i = 0; i < numRoots; i++) {
		if (r[i]->findTarget(n)) {
//			cout << "adding children to " << r[i]->findTarget(n)->getName() << endl; 
			r[i]->findTarget(n)->addChildren(d);
			exists = true;
			break;
		}
	}
	if (!exists) {
//		cout << "adding r " << n << " at " << numRoots + 1 << endl;
		tmpRoot = new Target *[numRoots + 1];
		for (int i = 0; i < numRoots; i++) {
			tmpRoot[i] = r[i];
		}
		tmpRoot[numRoots + 1] = new Target(n);
		tmpRoot[numRoots + 1]->addChildren(d);
		numRoots++;
	}
}

