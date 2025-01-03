#include "BST.h"
#include "BST_TestHarness.h"

int main()
{
    BST tree;
    TestHarness::TestBST::Insert(tree);
    TestHarness::TestBST::Exists(tree);
    return 0;
}