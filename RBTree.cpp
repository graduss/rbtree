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

Node* RBTree::btInsert(Node* n){
    Node* root = this->root;
    Node* x = 0;

    while(root){
        x = root;
        if(root->key > n->key) root = root->l;
        else root = root->r;
    }

    n->p = x;
    if (!x) this->root = n;
    else if(x->key > n->key) x->l = n;
    else x->r = n;

    return n;
}

Node* RBTree::insert(Node* x){
    btInsert(x);
    x->red = true;

    Node* y;
    while (x != root && x->p->red){
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
                x->p->p->red = true;
                rightRotate(x->p->p);
            }
        }else{ // родитель является правым ребенком.
            y = x->p->p->l;
            if(y && y->red){ // случей 1 (II)
                x->p->red = false;
                y->red = false;
                x->p->p->red = true;
                x = x->p->p;
            }else{
                if(x == x->p->l){ // случей 2 (II) -> случей 3 (II)
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

    return x;
}

Node* RBTree::remove(Node *n){
    Node* x = 0;
    Node* y = 0;
    bool imaginaryX = false;

    if(n->l == 0 || n->r == 0) y = n;
    else y = successor(n);

    if(y->l) x = y->l;
    else x = y->r;
    if(!x) {
        x = new Node;
        imaginaryX = true;
    }

    x->p = y->p;
    if(y->p == 0) root = x;
    else {
        if (y == y->p->l) y->p->l = x;
        else y->p->r = x;
    }

    if (y != n) n->key = y->key;

    if(!y->red) {
        rmoveFixup(x);
    }
    if (imaginaryX){
        if(x == x->p->l) x->p->l = 0;
        else x->p->r = 0;
        delete x;
        imaginaryX = false;
    }

    return y;
}

Node* RBTree::successor(Node *n) const {
    Node* ans;

    if(n->r){
        ans = min(n->r);
    }else{
        ans = n->p;
        while(ans && n == ans->r){
            n = ans;
            ans = ans->p;
        }
    }

    return ans;
}

Node* RBTree::predecessor(Node* n) const {
    Node* ans;

    if(n->l){
        ans = max(n->r);
    }else{
        ans = n->p;
        while(ans && n==ans->l){
            n = ans;
            ans = ans->p;
        }
    }

    return ans;
}

Node* RBTree::min(Node* root) const {
    Node* n;
    if(root) n = root;
    else n = this->root;

    while(n->l){
        n = n->l;
    }

    return n;
}

Node* RBTree::max(Node* root) const {
    Node* n;
    if(root) n = root;
    else n = this->root;

    while(n->l){
        n = n->l;
    }

    return n;
}

void RBTree::rmoveFixup(Node* x){
    Node* w;
    while (x != root && !x->red){
        if (x == x->p->l){
            w = x->p->r;
            if (w->red){ // случей 1 (I)
                w->red = false;
                w->p->red = true;
                leftRotate(x->p);
                w= x->p->r;
            }

            if (!w->l->red && !w->r->red) { // случей 2 (I)
                w->red = true;
                x = x->p;
            }else if(!w->r->red){ // случей 3 (I)
                w->l->red = false;
                w->red = true;
                rightRotate(w);
                w = x->p->r;
            }

            w->red = x->p->red; // случей 4 (I)
            x->p->red = false;
            w->r->red = false;
            leftRotate(x->p);
            x = root;
        }else{
            w = x->p->l;
            if(w->red){ // случей 1 (II)
                w->red = false;
                w->p->red = true;
                rightRotate(x->p);
                w = x->p->l;
            }

            if(!w->l->red && !w->r->red){ // случей 2 (II)
                w->red = true;
                x = x->p;
            }else if (!w->l->red) { // случей 3 (II)
                w->r->red = false;
                w->red = true;
                leftRotate(w);
                w = x->p->l;
            }

            w->red = x->p->red; // случей 4 (II)
            x->p->red = false;
            w->l->red = false;
            rightRotate(x->p);
            x = root;
        }
    }
}

void RBTree::inorderTreeWalk(const Node* n, int h)const {
    if(n){
        inorderTreeWalk(n->l, h+1);
        for(int i = h; i>0; i--){
            std::cout<<"->";
        }
        std::cout<<n->key<<" ";
        if(n->red) std::cout<<"red"<<std::endl;
        else std::cout<<"black"<<std::endl;
        inorderTreeWalk(n->r, h+1);
    }
}

void RBTree::show(){
    inorderTreeWalk(root);
    std::cout<<"************\n";
}

RBTree &RBTree::add(int key){
    Node* n = new Node(key);
    insert(n);

    return *this;
}

Node* RBTree::search(int key, Node* root) const {
    if(!root || key == root->key) return root;
    else if (key < root->key) return search(key, root->l);
    else return search(key, root->r);
}

RBTree& RBTree::del(int key){
    Node* n = search(key, root);
    if(n) remove(n);

    return *this;
}

}
