#include "Bst.hpp"


int main()
{
    BST<int> tree;

    tree.insert(5);
    tree.insert(3);
    tree.insert(7);
    tree.insert(2);

    tree.print();
    return 0;
}