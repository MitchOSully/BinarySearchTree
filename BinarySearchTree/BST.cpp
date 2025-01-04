#include "BST.h"
#include <iostream>
#include <queue> // for insertion
#include "Assert.h"


//template<typename T>
bool BST::insert(int elem)
{
    bool bSuccess = false;

    // Is tree empty?
    if (!pRoot)
    {
        pRoot = std::make_shared<Node>(elem);
        bSuccess = true;
    }
    else
    {
        std::shared_ptr<Node> pNext = pRoot;
        std::shared_ptr<Node> pCurr = nullptr;
        bool bDuplicateFound = false;
        while (pNext && !bDuplicateFound)
        {
            pCurr = pNext;
            if (elem < pCurr->data)
            {
                pNext = pCurr->pLeft;
            }
            else if (elem > pCurr->data)
            {
                pNext = pCurr->pRight;
            }
            else
            {
                bDuplicateFound = true;
            }
        }

        if (!bDuplicateFound)
        {
            // pNext should be nullptr here, meaning we reached
            // a node that has an empty left or right slot that 
            // the new element can go into
            if (elem < pCurr->data)
            {
                pCurr->pLeft = std::make_shared<Node>(elem);
                bSuccess = true;
            }
            else if (elem > pCurr->data)
            {
                pCurr->pRight = std::make_shared<Node>(elem);
                bSuccess = true;
            }
        }
    }

    return bSuccess;
}

bool BST::remove(int elem)
{
    bool bSuccess = false;

    if (pRoot)
    {
        if (elem == pRoot->data)
        {
            removeRoot();
            bSuccess = true;
        }

        std::shared_ptr<Node> pPrev = pRoot;
        std::shared_ptr<Node> pCurr = (elem < pRoot->data) ? pRoot->pLeft : pRoot->pRight;
        while (pCurr && !bSuccess)
        {
            if (elem < pCurr->data)
            {
                pPrev = pCurr;
                pCurr = pCurr->pLeft;
            }
            else if (elem > pCurr->data)
            {
                pPrev = pCurr;
                pCurr = pCurr->pRight;
            }
            else
            {
                removeNode(*pCurr, *pPrev);
                bSuccess = true;
            }
        }
    }

    return bSuccess;
}

void BST::removeRoot()
{
    // Replace root with its left child (arbitrary decision) and then find a place for the right
    // child in the children of the new root.
    putNodeInChildren(pRoot->pRight, *pRoot->pLeft);
    pRoot = pRoot->pLeft;
}

/// <summary>
/// removeNode
/// Removes 'node' from the tree, replacing it with one of its children if it has any.
/// If it has two children, we arbitrarily select the left child to replace it.
/// </summary>
/// <param name="node"></param>
/// <param name="parent"></param>
void BST::removeNode(BST::Node& node, BST::Node& parent)
{
    bool bIsLeftChild = (parent.pLeft && node.data == parent.pLeft->data);
    bool bIsRightChild = (parent.pRight && node.data == parent.pRight->data);
    ASSERTMSG(bIsLeftChild || bIsRightChild, "Parameters must be a parent-child pair");

    // Handle the children of the node we're removing
    if (!node.pLeft && !node.pRight)
    {
        // Node is a leaf. We can delete without any restructuring.
        parent.setChild(nullptr, bIsLeftChild);
    }
    else if (!node.pLeft && node.pRight)
    {
        // Node only has a right child. Replace the removed node with its only child.
        parent.setChild(node.pRight, bIsLeftChild);
    }
    else if (node.pLeft && !node.pRight)
    {
        // Node only has a left child. Replace the removed node with its only child.
        parent.setChild(node.pLeft, bIsLeftChild);
    }
    else // node.pLeft && node.pRight
    {
        // The removed node has two children. Replace it with its left child (arbitrary decision),
        // and find a place for the right child in the children of the left child.
        putNodeInChildren(node.pRight, *node.pLeft);
        parent.setChild(node.pLeft, bIsLeftChild);
    }
}

/// <summary>
/// putNodeInChildren
/// Finds a place for 'pNode' in the children of 'startNode'. Does a recursive search.
/// </summary>
/// <param name="pNode"></param>
/// <param name="startNode"></param>
void BST::putNodeInChildren(const std::shared_ptr<BST::Node> pNode, BST::Node& startNode)
{
    ASSERT(pNode);
    ASSERT(pNode->data != startNode.data);

    if (pNode->data < startNode.data) // Put in left branch
    {
        if (!startNode.pLeft)
        {
            startNode.pLeft = pNode; // Done
        }
        else
        {
            putNodeInChildren(pNode, *startNode.pLeft); // Recurse. Try putting pNode in pLeft's children.
        }
    }
    else if (pNode->data > startNode.data) // Put in right branch
    {
        if (!startNode.pRight)
        {
            startNode.pRight = pNode; // Done
        }
        else
        {
            putNodeInChildren(pNode, *startNode.pRight); // Recurse. Try putting pNode in pRight's children
        }
    }
}

void BST::Node::setChild(std::shared_ptr<Node> pNewChild, bool bLeft)
{
    if (bLeft)
    {
        pLeft = pNewChild;
    }
    else
    {
        pRight = pNewChild;
    }
}

bool BST::exists(int elem)
{
    bool bFound = false;

    std::shared_ptr<Node> pCurr = pRoot;
    while (pCurr && !bFound)
    {
        if (elem < pCurr->data)
        {
            pCurr = pCurr->pLeft;
        }
        else if (elem > pCurr->data)
        {
            pCurr = pCurr->pRight;
        }
        else
        {
            bFound = true;
        }
    }

    return bFound;
}

// currently unused
std::shared_ptr<BST::Node> BST::search(int elem)
{
    std::shared_ptr<Node> pTarget = nullptr;

    std::shared_ptr<Node> pNext = pRoot;
    while (pNext && !pTarget)
    {
        std::shared_ptr<Node> pCurr = pNext;
        if (elem < pCurr->data)
        {
            pNext = pCurr->pLeft;
        }
        else if (elem > pCurr->data)
        {
            pNext = pCurr->pRight;
        }
        else
        {
            pTarget = pCurr;
        }
    }

    return pTarget;
}

/// <summary>
/// print
/// Prints the contents of the tree in sorted order.
/// </summary>
void BST::print(bool bCompact /*= true*/)
{
    if (bCompact)
    {
        std::cout << "{ ";
    }

    if (pRoot)
    {
        printThisAndAllChildren(*pRoot, bCompact);
    }

    if (bCompact)
    {
        std::cout << "}\n";
    }
}

/// <summary>
/// printThisAndAllChildren
/// Recursively prints all the left children first, then the current node, then all the right children.
/// </summary>
/// <param name="node"></param>
/// <param name="bCompact"></param>
void BST::printThisAndAllChildren(const BST::Node& node, bool bCompact /*= true*/)
{
    if (node.pLeft)
    {
        printThisAndAllChildren(*node.pLeft, bCompact);
    }

    std::cout << node.data;
    if (bCompact)
    {
        std::cout << " ";
    }
    else
    {
        std::cout << '\n';
    }

    if (node.pRight)
    {
        printThisAndAllChildren(*node.pRight, bCompact);
    }
}