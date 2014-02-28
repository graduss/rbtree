#include "RBTree.h"

namespace rbt{

RBTree::RBTree():
    root(0)
{}

RBTree::~RBTree() {
    if(root){
        delete root;
    }
}

void RBTree::leftRotate(const Node* x){
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

void RBTree::rightRotate(const Node* x){
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

Node* RBTree::btInsert(const Node* n){
    Node* root = this->root;
    Node* x;

    while(root){
        x = root;
        if(root->key > n->key) root = root->l;
        else root = root->r;
    }

    n->p = x;
    if (x == 0) this->root = n;
    else if (x->key > n->key) x->l = n;
    else x->r = n;

    return n;
}

Node* RBTree::insert(const Node* n){
    btInsert(n);
    n->red = true;

    Node* y;
    while (n !== root && n->p->red){
        if(x->p == x->p->l){
            y = x->p->r;
            if(y->red){
                x->p->red = false;
                y->red = false;
                x->p->p->red = true;
                x = x->p->p;
            }
        }
    }
}

}
