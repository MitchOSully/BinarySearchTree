#include "BST.h"
#include "BST_TestHarness.h"

int main()
{
    BST tree;
    TestHarness::TestBST::Insert(tree);
    TestHarness::TestBST::Exists(tree);
    TestHarness::TestBST::Remove(tree);
    return 0;
}