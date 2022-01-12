#ifndef FLIPPEDTREE_H
#define FLIPPEDTREE_H

#include "Group.h"

struct FlippedTreeNode{

    FlippedTreeNode* father;
    int index;
    int TotalSons;
    Group* GP;
    FlippedTreeNode** Sons;
};

#endif //FLIPPEDTREE_H
