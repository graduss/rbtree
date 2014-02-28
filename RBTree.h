#include "Node.h"

#ifndef RBTREE_H
#define RBTREE_H

namespace rbt{

class RBTree
{
    public:
        RBTree();
        virtual ~RBTree();

        void leftRotate(const Node* n);
        void rightRotate(const Node* x);

        Node* insert(const Node* n);
    protected:
    private:
        Node* root;
        Node* btInsert(const Node* n);
};

};

#endif // RBTREE_H
