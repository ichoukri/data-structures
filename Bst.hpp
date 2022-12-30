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

    Node(T &value, Node *parent, Node *left, Node *right)
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
};

#endif
