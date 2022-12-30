#ifndef BST_HPP
#define BST_HPP

#include <iostream>

template <class T, class Allocator = std::allocator<T> >
struct Node
{
    T _key;
    Node *_left;
    Node *_right;
    Node *_parent;
    Allocator _alloc;
    typename Allocator::size_type _hieght;

    Node(T const &value, Node *parent, Node *left, Node *right)
    {
        _hieght = 1;
        _alloc.construct(&_key, value);
        _parent = parent;
        _right = right;
        _left = left;
    }
    ~Node()
    {
        _alloc.destroy(&_key);
    }
};

template <class T, class Allocator = std::allocator<T> >
class BST
{
private:
    typedef struct Node<T, Allocator> Node;
    Node *_root;

public:
    BST() : _root(NULL) {}

    BST(BST &copy) : _root(copy._root) {}

    BST &operator=(BST &rhs)
    {
        _root = rhs._root;
        return *this;
    }
    ~BST() {}
    void insert(T const &value)
    {
        insert(_root, value, NULL);
    }

    void print()
    {
        PostOrderTraversal(_root, &BST::print);
    }

    private:
    size_t height(Node *root)
    {
        if (root == NULL)
            return 0;
        return root->_hieght;
    }
    template <typename U>
    U max(U a, U b)
    {
        return (a > b) ? a : b;
    }

    void insert(Node *&root, T const &value, Node *parent)
    {
        if (root == NULL)
        {
            root = new Node(value, parent, NULL, NULL);
            return;
        }
        if (value < root->_key)
        {
            insert(root->_left, value, root);
            root->_hieght = 1 + max(height(root->_left), height(root->_right));
        }
        else
        {
            insert(root->_right, value, root);
            root->_hieght = 1 + max(height(root->_left), height(root->_right));
        }
    }
};

#endif
