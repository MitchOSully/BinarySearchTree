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

        int data;
        std::shared_ptr<Node> pLeft = nullptr;
        std::shared_ptr<Node> pRight = nullptr;
    };

    std::shared_ptr<Node> search(int elem);

    std::shared_ptr<Node> pRoot = nullptr;
};
