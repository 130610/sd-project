#include <iostream>
#include "target.h"
using namespace std;

int main()
{
	Target **root = new Target*[1];
	root[0] = parseTargets("BryanMakefile.txt");
	root[0]->initPositions();
	root[0]->printTree();
	root[0]->findTarget("cat")->printTree();
	root[0]->findTarget("tar1.o")->printTree();
	return 0;
}
