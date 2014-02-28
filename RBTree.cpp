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

Node* RBTree::insert(const Node* x){
    btInsert(x);
    x->red = true;

    Node* y;
    while (x !== root && x->p->red){
        if(x->p == x->p->p->l){ // родитель является левым ребенком.
            y = x->p->p->r;
            if(y && y->red){ // случей 1 (I)
                x->p->red = false;
                y->red = false;
                x->p->p->red = true;
                x = x->p->p;
            }else {
                if (x == x->p->r) { // случей 2 (I) -> случей 3 (I)
                    x = x->p;
                    leftRotate(x);
                }
                x->p->red = false; // случей 3 (I)
                x->p->p->reg = true;
                rightRotate(x->p->p);
            }
        }else{ // родитель является правым ребенком.
            y = x->p->p->l;
            if(Y && y->red){ // случей 1 (II)
                x->p->red = false;
                y->red = false;
                x->p->p = true;
                x = x->p->p;
            }else{
                if(x == x->p->r){ // случей 2 (II) -> случей 3 (II)
                    x = x->p;
                    rightRotate(x);
                }
                x->p->red = false; // сулчей 3 (II)
                x->p->p->red = true;
                leftRotate(x->p->p);
            }
        }
    }
    root->red = false;
}

}
