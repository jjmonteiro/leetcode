#include <stdexcept>
#include <string>
#include <iostream>

class Node
{
public:
    Node(int value, Node* left, Node* right)
    {
        this->value = value;
        this->left = left;
        this->right = right;
    }

    int getValue() const
    {
        return value;
    }

    Node* getLeft() const
    {
        return left;
    }

    Node* getRight() const
    {
        return right;
    }

private:
    int value;
    Node* left;
    Node* right;
};

class BinarySearchTree
{
public:
    static bool contains(const Node& root, int value)
    {
        // The given key is
        // not found in BST
        if (&root == NULL)
            return NULL;
        // The given key is found
        else if (root.getValue() == value)
            return &root;
        // The given is greater than
        // current node's key
        else if (root.getValue() < value)
            return contains(*root.getRight(), value);
        // The given is smaller than
        // current node's key
        else
            return contains(*root.getLeft(), value);
    }
};

#ifndef RunTests
int main()
{
    Node n1(1, NULL, NULL);
    Node n3(3, NULL, NULL);
    Node n2(2, &n1, &n3);

    std::cout << BinarySearchTree::contains(n2, 4);
}
#endif