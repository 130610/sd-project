#include <string>
#include "MfTree.h"

MfNode::MfNode(MfNode *p, string n) : targetName(n), numParent(1), numChild(0), orphan(false)
{
  childNodes = new MfNode * [1];
  parentNodes = new MfNode * [1];
  childNodes[0] = 0;
  parentNodes[0] = p;

  p->orphan = false;
  p->addChild(this);
}

MfNode::addChild(MfNode *c)
{
  MfNode **tmp = new MfNode * [numChild + 1]
  for (int i = 0; i < numChild; i++) {
    tmp[i] = childNodes[i];
  }
  tmp[numChild] = c;
  numChild++;
  delete [] childNodes;
  childNodes = tmp;

  
}
