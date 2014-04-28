#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include "target.h"
using namespace std;

void Target::addChildren(string dl)
{
	Target **tmpList;
	SplitString depends(dl);
	vector<string> dependsList = depends.split(' ');
	tmpList = new Target*[numChildren + dependsList.size()];

	for (int i = 0; i < numChildren; i++) {
		tmpList[i] = children[i];
	}
	for (int i = 0; i < dependsList.size(); i++) {
		tmpList[i + numChildren] = new Target(dependsList[i]);
	}

	delete [] children;
	children = tmpList;
}

vector<string>& SplitString::split(char delim)
{
	if (!flds.empty()) flds.clear();
	string work = data();
	string buf = "";
	int i = 0;
	while (i < work.length()) {
		if (work[i] != delim) {
			buf += work[i];
		} else if (buf.length() > 0) {
			flds.push_back(buf);
			buf = "";
		}
		i++;
	}
	if (!buf.empty()) {
		flds.push_back(buf);
	}
	return flds;
}

Target *parseTargets(const char *filename)
{
	Target *root;
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
			root = new Target(tName);
			root->addChildren(tDepends);
			numTargets++;
			cout << "made root at " << i << endl;
		} else if (matchTargetLine(lineList[i], tName, tDepends)) {
			cout << "found target at " << i << endl;
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
	int i = 0;
	bool inName = true;
	n = d = "";

	if (l[0] == '\t' || l[0] == '\n') {
		return false;
	}

	while (l[i] != '\n' && i < l.length()) {
		if (l[i] == ':'){
			inName = false;
			while (l[++i] == ' ');
		} else if (inName) {
			n.append(1, l[i]);
		} else if (!inName) {
			d.append(1, l[i]);
		}
		i++;
	}
	return true;
}

