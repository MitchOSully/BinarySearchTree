#include "BST_TestHarness.h"
#include <iostream>
#include <string>
#include <array>
#include "BST.h"

using std::string;

#define TEST_CONSOLE_OUTPUT(sExpected, func)                  \
    std::cout << "EXPECTED: " << sExpected << " RECEIVED: ";  \
    func();                                                   \

#define TEST_ASSERT(sTestName, bBool)    \
    std::cout << sTestName << ": "; \
    if (bBool)                      \
        std::cout << "SUCCESS\n";   \
    else                            \
        std::cout << "FAILED\n";    \

const std::array<int, 5> aElems = { 4, 1, 9, 2, 6 }; 

void TestHarness::TestBST::Insert(BST& tree)
{
    TEST_CONSOLE_OUTPUT("{}", tree.print);

    for (int elem : aElems)
    {
        TEST_ASSERT("Inserting " + std::to_string(elem), tree.insert(elem));
    }
    TEST_ASSERT("Inserting duplicate should fail", !tree.insert(9));
    TEST_CONSOLE_OUTPUT("{4, 1, 9, 2, 6}", tree.print);
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
}
