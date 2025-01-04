#pragma once
#include <memory> // for unique_ptr

//template<typename T>
class BST
{
public:
    bool insert(int elem);
    bool remove(int elem);
    bool exists(int elem);

    void print(bool bCompact = true);
private:
    class Node
    {
    public:
        Node() = delete;
        Node(int inData) : data(inData) {}

        void setChild(std::shared_ptr<Node> pNewChild, bool bLeft);

        int data;
        std::shared_ptr<Node> pLeft = nullptr;
        std::shared_ptr<Node> pRight = nullptr;
    };

    std::shared_ptr<Node> search(int elem);
    void removeRoot();
    void removeNode(Node& node, Node& parent);
    void putNodeInChildren(const std::shared_ptr<Node> pNode, Node& startNode);
    void printThisAndAllChildren(const Node& node, bool bCompact = true);

    std::shared_ptr<Node> pRoot = nullptr;
};
