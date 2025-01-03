#include "BST.h"
#include <iostream>
#include <queue> // for insertion


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
    return false;
}

bool BST::exists(int elem)
{
    std::shared_ptr<Node> pNode = search(elem);
    return !!pNode;
}

std::shared_ptr<BST::Node> BST::search(int elem)
{
    std::shared_ptr<Node> pTarget = nullptr;

    if (pRoot)
    {
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
    }

    return pTarget;
}

/// <summary>
/// print()
/// Prints the contents of the tree (not in sorted order).
/// If tree is empty, prints the newline character.
/// </summary>
void BST::print(bool bCompact /*= true*/)
{
    if (bCompact)
    {
        std::cout << '{';
    }

    if (pRoot)
    {
        std::queue<std::shared_ptr<Node>> q;
        q.push(pRoot);
        while (!q.empty())
        {
            std::shared_ptr<Node> pCurr = q.front(); // Get front element
            q.pop(); // Remove front element
            if (pCurr)
            {
                std::cout << pCurr->data;
                if (pCurr->pLeft)
                {
                    q.push(pCurr->pLeft);
                }
                if (pCurr->pRight)
                {
                    q.push(pCurr->pRight);
                }

                if (!q.empty())
                {
                    if (bCompact)
                    {
                        std::cout << ", ";
                    }
                    else
                    {
                        std::cout << '\n';
                    }
                }
            }
            else // if (pCurr)
            {
                std::cout << "\nBST ERROR: null node during printing\n";
            }
        }
    }

    if (bCompact)
    {
        std::cout << '}';
    }

    std::cout << '\n';
}