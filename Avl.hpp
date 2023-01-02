#ifndef AVL_HPP
#define AVL_HPP

#include "Bst.hpp"

template <class T, class Allocator = std::allocator<T> >
class AVL : public BST<T, Allocator> 
{
    typedef struct BST<T, Allocator> BST;
    typedef struct Node<T, Allocator> Node;
public:
    AVL() : BST() {}
    AVL(AVL &copy) : BST(copy) {}
    AVL &operator=(AVL &rhs)
    {
        BST::operator=(rhs);
        return *this;
    }
    ~AVL() {
    }
    void insert(T const &value)
    {
        Node *tmp =  BST::insert(BST::_root, value, NULL);

        int height = 0;
        while(tmp != NULL) // balance tree from the inserted node to the root
        {
            height = BST::height(tmp->_left) - BST::height(tmp->_right);

            if (height > 1) // left rotate
            {
                if (value > *tmp->_left->_key) // left right rotate
                    left_rotate(tmp->_left);
                right_rotate(tmp);
            }
            else if (height < -1) // right rotate
            {
                if (value < *tmp->_right->_key) // right left rotate
                    right_rotate(tmp->_right);
                left_rotate(tmp);
            }
            tmp = tmp->_parent;
        }
    }

private:
    void left_rotate(Node *node)
    {
        Node *tmp = node->_right;

        if (tmp->_left != NULL)
            tmp->_left->_parent = node;
        node->_right = tmp->_left;
        tmp->_left = node;
        if (node->_parent != NULL)
        {
            if (node->_parent->_left == node)
                node->_parent->_left = tmp;
            else
                node->_parent->_right = tmp;
        }
        else
            BST::_root = tmp;
        tmp->_parent = node->_parent;
        node->_parent = tmp;
        node->_hieght = 1 + std::max(BST::height(node->_left), BST::height(node->_right));
        tmp->_hieght = 1 + std::max(BST::height(tmp->_left), BST::height(tmp->_right));
    }

    void right_rotate(Node *&node)
    {
        Node *tmp = node->_left;

        node->_left = tmp->_right;
        tmp->_right = node;
        if (node->_parent != NULL)
        {
            if (node->_parent->_left == node)
                node->_parent->_left = tmp;
            else
                node->_parent->_right = tmp;
        }
        else
            BST::_root = tmp;
        tmp->_parent = node->_parent;
        node->_parent = tmp;
        node->_hieght = 1 + std::max(BST::height(node->_left), BST::height(node->_right));
        tmp->_hieght = 1 + std::max(BST::height(tmp->_left), BST::height(tmp->_right)); 
    }
};

#endif