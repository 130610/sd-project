#include <iostream>
#include "target.h"
using namespace std;

int main()
{
	Target **root = new Target*[1];
	root[0] = parseTargets("TestMakefile2");
	root[0]->initPositions();
	root[0]->printTree();
	root[0]->findTarget("dep1")->printTree();
	root[0]->findTarget("dep1.o")->printTree();
	root[0]->findTarget("dep2")->printTree();
	root[0]->findTarget("dep2.o")->printTree();
	return 0;
}
