#include "RBTree.h"

namespace rbt{

RBTree::RBTree():
    root(0)
{}

RBTree::~RBTree()
{
    if(root){
        delete root;
    }
}

void RBTree::leftRotate(Node* x){
    Node* y = x->r;
    x->r = y->l;

    if(y->l) y->l->p = x;
    y->p = x->p;

    if(x->p == 0) root = y;
    else if(x == x->p->l) x->p->l = y;
    else x->p->r = y;

    y->l = x;
    x->p = y;
}

void RBTree::rightRotate(Node* x){
    Node* y = x->l;

    x->l = y->r;
    if(y->r) y->r->p = x;

    y->p = x->p;

    if(x->p == 0) root = y;
    else if(x == x->p->l) x->p->l = y;
    else x->p->r = y;

    y->r = x;
    x->p = y;
}

}
