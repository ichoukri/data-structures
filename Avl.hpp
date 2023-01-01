#ifndef AVL_HPP
#define AVL_HPP

#include "Bst.hpp"

template <class T, class Allocator = std::allocator<T> >
class AVL : public BST<T, Allocator> 
{
    typedef struct BST<T, Allocator> BST;
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
        BST::insert(value);
    }
private:
};

#endif