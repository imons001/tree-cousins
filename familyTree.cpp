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

int FamilyTree::numberOfCousins() const {
    if(parent == nullptr || parent->parent == nullptr){
        return 0;
    }
    
    FamilyTree *grandparent = parent->parent;
    int cousinsCount = 0;

    for (FamilyTree *uncleOrAunt : grandparent->children){
        if (uncleOrAunt == parent)
            continue;{
        cousinsCount += uncleOrAunt->children.size();
        }
    }

    return cousinsCount;
}

FamilyTree *FamilyTree::find(int identifier) {
    if (this->identifier == identifier)
        return this;

    for (FamilyTree *child : children) {
        FamilyTree *result = child->find(identifier);
        if (result != nullptr)
            return result;
    }

    return nullptr;
}

const FamilyTree *FamilyTree::find(int identifier) const {
    if (this->identifier == identifier)
        return this;

    for (FamilyTree *child : children) {
        const FamilyTree *result = child->find(identifier);
        if (result != nullptr)
            return result;
    }

    return nullptr;
}



