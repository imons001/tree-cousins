#include <list>
#include <queue>
#include <vector>
#include <iostream>
#include <fstream>

#include "familyTree.h"


using namespace std;


FamilyTree* readNode (istream& in, FamilyTree* parent)
{
    char c;
    in >> c;
    if (c == '(')
    {
        int id;
        in >> id;
        FamilyTree* newNode = new FamilyTree(id, parent);
        while (c != ')')
        {
            in >> c;
            if (c != ')')
            {
                in.unget();
                readNode(in, newNode);
            }
        }
        return newNode;
    }
    else // should be a numeric digit
    {
        in.unget();
        int id;
        in >> id;
        return new FamilyTree(id, parent);
    }
}


void readTree (istream& in, FamilyTree*& root, FamilyTree*& interest)
{
    int idOfInterest;
    in >> idOfInterest;

    root = readNode(in, nullptr);

    interest = root->find(idOfInterest);
}



void solve (istream& in)
{
    FamilyTree* root;
    FamilyTree* nodeOfInterest;
    readTree (in, root, nodeOfInterest);
    cout << nodeOfInterest->numberOfCousins() << endl;
}

int main (int argc, char** argv)
{
    if (argc > 1)
    {
        ifstream in (argv[1]);
        solve(in);
        in.close();
    }
    else
       solve(cin);
    return 0;
}


