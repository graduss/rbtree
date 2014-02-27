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
    protected:
    private:
        Node *root;
};

};

#endif // RBTREE_H
