#include <list>
#include <queue>
#include <vector>
#include <iostream>

#include "familyTree.h"

using namespace std;


FamilyTree::FamilyTree (int id, FamilyTree* theParent)
: identifier(id), parent(theParent)
{
    if (parent != nullptr)
        parent->children.push_back(this);
}

FamilyTree::~FamilyTree()
{
    for (FamilyTree* child: children)
        delete child;
}



