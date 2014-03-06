#include "Node.h"
#include <iostream>

#ifndef RBTREE_H
#define RBTREE_H

namespace rbt{

class RBTree
{
    public:
        RBTree();
        virtual ~RBTree();

        void show();
        RBTree& add(int key);
        RBTree& del(int key);

        void leftRotate(Node* n);
        void rightRotate(Node* x);

        Node* insert(Node* n);
        Node* remove(Node* n);
        Node* successor(Node* n) const;
        Node* predecessor(Node* n) const;
        Node* min(Node* root = 0) const;
        Node* max(Node* root = 0) const;
        Node* search(int key, Node* root) const;
    private:
        Node* root;
        Node* btInsert(Node* n);
        void rmoveFixup(Node* x);
        void inorderTreeWalk(const Node *n, int h = 0) const;
};

};

#endif // RBTREE_H
