#include "BST_TestHarness.h"
#include <iostream>
#include <string>
#include <array>
#include "BST.h"

using std::string;

#define TEST_CONSOLE_OUTPUT(sExpected, func)                  \
    std::cout << "EXPECTED: " << sExpected << "\nRECEIVED: "; \
    func();                                                   \

#define TEST_ASSERT(sTestName, bBool)    \
    std::cout << sTestName << ": "; \
    if (bBool)                      \
        std::cout << "SUCCESS\n";   \
    else                            \
        std::cout << "FAILED\n";    \

const std::array<int, 8> aElems = { 4, 1, 9, 2, 6, 11, 5, 7 }; 

void TestHarness::TestBST::Insert(BST& tree)
{
    TEST_CONSOLE_OUTPUT("{}", tree.print);

    for (int elem : aElems)
    {
        TEST_ASSERT("Inserting " + std::to_string(elem), tree.insert(elem));
    }
    TEST_ASSERT("Inserting duplicate should fail", !tree.insert(9));
    TEST_CONSOLE_OUTPUT("{ 1 2 4 5 6 7 9 11 }", tree.print);
}

void TestHarness::TestBST::Exists(BST& tree)
{
    for (int elem : aElems)
    {
        TEST_ASSERT("Checking node " + std::to_string(elem) + " exists", tree.exists(elem));
    }
    TEST_ASSERT("Check node 14 does not exist", !tree.exists(14));
}

void TestHarness::TestBST::Remove(BST& tree)
{
    TEST_ASSERT("Removing 5 (a leaf)",                   tree.remove(5));
    TEST_CONSOLE_OUTPUT("{ 1 2 4 6 7 9 11 }", tree.print);
    TEST_ASSERT("Removing 1 (a node with one child)",    tree.remove(1));
    TEST_CONSOLE_OUTPUT("{ 2 4 6 7 9 11 }", tree.print);
    TEST_ASSERT("Removing 9 (a node with two children)", tree.remove(9));
    TEST_CONSOLE_OUTPUT("{ 2 4 6 7 11 }", tree.print);
    TEST_ASSERT("Removing 4 (the root)",                 tree.remove(4));
    TEST_CONSOLE_OUTPUT("{ 2 6 7 11 }", tree.print);
}
