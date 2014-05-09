#include <iostream>
#include "target.h"
using namespace std;

int main()
{
	Target **root;
	root = parseTargets("Makefile.level");
	root[0]->initPositions();
	root[0]->printTree();
	root[0]->findTarget("dep1")->printTree();
	root[0]->findTarget("dep1.o")->printTree();
	root[0]->findTarget("dep2")->printTree();
	root[0]->findTarget("dep2.o")->printTree();
  unsigned i = root[0]->getNumTargets();
  cout << "depth: " << i << endl;
	return 0;
}
