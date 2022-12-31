#ifndef BST_HPP
#define BST_HPP

#include <iostream>

template <class T, class Allocator = std::allocator<T> >
struct Node
{
    T *_key;
    Node *_left;
    Node *_right;
    Node *_parent;
    Allocator _alloc;
    typename Allocator::size_type _hieght;

    Node(T const &value, Node *parent, Node *left, Node *right)
    {
        _hieght = 1;
        _key = _alloc.allocate(1);
        _alloc.construct(_key, value);
        _parent = parent;
        _right = right;
        _left = left;
    }
    ~Node()
    {
        _alloc.destroy(_key);
        _alloc.deallocate(_key, 1);
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

    void remove(T const &value)
    {
        Node *temp = remove(value, _root, NULL);
        if (temp != NULL)
        {
            delete temp;
            temp = NULL;
            update_height(_root);
        }
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
        if (value < *root->_key)
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

    void PostOrderTraversal(Node *root, void (BST::*func)(Node *))
    {
        if (root == NULL)
            return;
        PostOrderTraversal(root->_left, func);
        PostOrderTraversal(root->_right, func);
        (this->*func)(root);
    }
    void print(Node *root)
    {
        std::cout << *root->_key << std::endl;
    }

    Node *find_min(Node *root)
    {
        if (root == NULL)
            return NULL;
        if (root->_left == NULL)
            return root;
        return find_min(root->_left);
    }

    Node *remove(T const &value, Node *&root, Node *parent)
    {
        Node *temp = NULL;
        Node *successor;

        if (root == NULL)
            return NULL;
        if (value < *root->_key)
            return remove(value, root->_left, root);
        else if (value > *root->_key)
            return remove(value, root->_right, root);
        else
        {
            temp = root;
            if (root->_left == NULL && root->_right == NULL)
                successor = NULL;
            else if (root->_left == NULL)
                successor = root->_right;
            else if (root->_right == NULL)
                successor = root->_left;
            else
            {
                Node *min = find_min(root->_right);
                swap(root->_key, min->_key);
                return remove(value, root->_right, root);
            }
            if (_root == root)
                _root = successor;
            else if (parent->_left == root)
                parent->_left = successor;
            else
                parent->_right = successor;
        }
        return temp;
    }

    void update_height(Node *root)
    {
        if (root == NULL)
            return;
        root->_hieght = 1 + max(height(root->_left), height(root->_right));
    }
    void swap(T *a, T *b)
    {
        T temp = *a;
        *a = *b;
        *b = temp;
    }
};

#endif
