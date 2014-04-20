#ifndef _MFTREE_
#define _MFTREE_

#include <string>
using namespace std;

// a tree with an arbitrary amount of parents and children for each node
class MfNode
{
protected:
  string targetName;
  MfNode **parentNodes;
  MfNode **childNodes;
  int numParent;
  int numChild;
  bool orphan;
public:
  MfNode(MfNode *p, string n);
  MfNode() : orphan(true) {}

  string getName() { return name; }
};

#endif
