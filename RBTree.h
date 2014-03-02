#include "Node.h"

#ifndef RBTREE_H
#define RBTREE_H

namespace rbt{

class RBTree
{
    public:
        RBTree();
        virtual ~RBTree();

        void leftRotate(Node* n);
        void rightRotate(Node* x);

        Node* insert(Node* n);
    protected:
    private:
        Node* root;
        Node* btInsert(Node* n);
};

};

#endif // RBTREE_H
