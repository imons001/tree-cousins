#include "unittest.h"
#include "familyTree.h"
#include <algorithm>

using namespace std;

struct Setup
{
    /**
     * Build a tree in the form
     * 
     * 1-\
     *    |-2-\
     *    |   |-3
     *    |   |-4
     *    | 
     *    |-5-\
     *    |    |-6-\
     *    |    |    |-7
     *    |    |-8
     *    |    |-9
     */

    FamilyTree *root;

    Setup()
    {
        root = new FamilyTree(1, nullptr);
        FamilyTree *node2 = new FamilyTree(2, root);
        FamilyTree *node5 = new FamilyTree(5, root);

        /*FamilyTree *node3 =*/ new FamilyTree(3, node2);
        /*FamilyTree *node4 =*/ new FamilyTree(4, node2);

        FamilyTree *node6 = new FamilyTree(6, node5);
        /*FamilyTree *node8 =*/ new FamilyTree(8, node5);
        /*FamilyTree *node9 =*/ new FamilyTree(9, node5);
        /*FamilyTree *node7 =*/ new FamilyTree(7, node6);
    }

    ~Setup()
    {
        delete root;
    }
};

UnitTest(testSetup)
{
    Setup s;
    assertThat(s.root->getIdentifier(), isEqualTo(1));
    assertThat(s.root->getParent(), isNull());
    int expected[] = {2, 5};
    int ctr = 0;
    for (FamilyTree *child : *(s.root))
    {
        assertThat(child->getIdentifier(), isEqualTo(expected[ctr]));
        ++ctr;
        assertThat(child->getParent(), isEqualTo(s.root));
    }
}

UnitTest(testFind)
{
    Setup s;

    for (int i = 1; i < 10; ++i)
    {
        FamilyTree *node = s.root->find(i);
        assertThat(node, isNotNull());
        assertThat(node->getIdentifier(), isEqualTo(i));
        if (i > 1)
        {
            assertThat(node->getIdentifier(), isGreaterThan(node->getParent()->getIdentifier()));
        }
    }
    FamilyTree *n2 = s.root->find(2);
    const FamilyTree *node2 = n2;
    for (int i = 3; i < 5; ++i)
    {
        const FamilyTree *node = node2->find(i);
        assertThat(node, isNotNull());
        assertThat(node->getIdentifier(), isEqualTo(i));
        assertThat(node->getParent(), isEqualTo(node2));
    }
    assertThat(n2->find(1), isNull());
    assertThat(node2->find(7), isNull());
}

UnitTest(testCousins)
{
    Setup s;

    FamilyTree *n1 = s.root->find(1);
    assertThat(n1->numberOfCousins(), isEqualTo(0));
    assertThat(((const FamilyTree *)n1)->numberOfCousins(), isEqualTo(0));

    FamilyTree *n2 = s.root->find(2);
    assertThat(n2->numberOfCousins(), isEqualTo(0));

    FamilyTree *n3 = s.root->find(3);
    assertThat(n3->numberOfCousins(), isEqualTo(3));

    const FamilyTree *n6 = s.root->find(6);
    assertThat(n6->numberOfCousins(), isEqualTo(2));

    const FamilyTree *n7 = s.root->find(7);
    assertThat(n7->numberOfCousins(), isEqualTo(0));
}