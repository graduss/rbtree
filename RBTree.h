#include "exceptions/RBTreeException.h"
#include "smartpointer/SPointer.h"
#include "iterator/iterator.h"
#include <iostream>

#ifndef RBTREE_H
#define RBTREE_H

namespace rbt{

class RBTree {

public:
    RBTree(): p(0) {}
    ~RBTree();

    RBTree& add(int key);
    RBTree& del(int key);

    int successor(int key) const;
    int predecessor(int key) const;
    int min() const;
    int max() const;

    Iterator begin() const;
    Iterator end() const;

    bool isThere(int key) const;

    /********** testing **************/
    void show() const;

private:
    class Private;
    Private *p;
};

};

#endif // RBTREE_H
