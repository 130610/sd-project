#include <iostream>
#include <fstream>
#include <string>
#include "target.h"
using namespace std;

Target *parseTargets(const char *filename)
{
	string *lineList = new string[1]; 
	char line[128];
	char c;
	int i = 0;
	ifstream ifs(filename);

	while (ifs >> c) {
		line[i++] = c;
		if (c == '\n') {
			line[i] = '\0';
			addLine(lineList, line);
			i = 0;
		}
	}
	while (lineList[i++] != "") cout << lineList[i] << endl << endl;
	return 0;
}

void addLine(string *ll, char l[])
{
	string *tmpList;
	int len = 0;

	while (ll[len++] != "")
	tmpList = new string[len + 1];

	for (int i = 0; i < len; i++) {
		tmpList[i] = ll[i];
	}
	tmpList[len] = l;

	delete [] ll;
	ll = tmpList;
}
