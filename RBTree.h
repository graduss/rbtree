#include "smartpointer/SPointer.h"
#include <iostream>

#ifndef RBTREE_H
#define RBTREE_H

namespace rbt{

template <class Data>
class RBTree {

public:
    RBTree(): root(0) {}
    ~RBTree();

    RBTree& add(const Data& key);
    RBTree& del(const Data& key);

    Data& successor(const Data& key) const;
    Data& predecessor(const Data& key) const;
    Data& min(const Data& key) const;
    Data& max(const Data& key) const;

    /********** testing **************/
    void show() const;

private:
    struct Item{
        Data key;
        bool red;
        SPointer<Item> l, r, p;

        Item(const Data& k): key(k), red(false), l(0), r(0), p(0) {}
        Item(const Item& i);
        ~Item();
    };
    SPointer<Item> root;

    void leftRotate(SPointer<Item> x);
    void rightRotate(SPointer<Item> x);
    void btInsert(SPointer<Item>& x);
    void insert(SPointer<Item>& x);

    /******* testing ***********/
    void inorderTreeWalk(const SPointer<Item>& n, int h = 0)const;
};
/*******
** RBTree
**/
template<class Data>
RBTree<Data>& RBTree<Data>::add(const Data& key){
    SPointer<Item> n = new Item(key);
    if(!n) throw "Mem Error";
    //std::cout<<n->key;
    insert(n);
    return *this;
}

template<class Data>
void RBTree<Data>::insert(SPointer<Item>& x){
    btInsert(x);
    x->red = true;

    SPointer<Item> y;
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
}

template<class Data>
void RBTree<Data>::btInsert(SPointer<Item>& n){
    SPointer<Item> root = this->root;
    SPointer<Item> x;

    while(root){
        x = root;
        if(root->key > n->key) root = root->l;
        else root = root->r;
    }

    n->p = x;
    if (!x) this->root = n;
    else if(x->key > n->key) x->l = n;
    else x->r = n;
}

template<class Data>
void RBTree<Data>::leftRotate(SPointer<Item> x){
    SPointer<Item> y = x->r;

    x->r = y->l;
    if(y->l) y->l->p = x;

    y->p = x->p;

    if(!x->p) root = y;
    else if(x == x->p->l) x->p->l = y;
    else x->p->r = y;

    y->l = x;
    x->p = y;
}

template<class Data>
void RBTree<Data>::rightRotate(SPointer<Item> x){
    SPointer<Item> y = x->l;

    x->l = y->r;
    if(y->r) y->r->p = x;

    y->p = x->p;

    if(!x->p) root = y;
    else if(x == x->p->l) x->p->l = y;
    else x->p->r = y;

    y->r = x;
    x->p = y;
}

template<class Data>
RBTree<Data>::~RBTree(){
    if(root) delete &root;
}
/**************** testting **********************************/
template<class Data>
void RBTree<Data>::inorderTreeWalk(const SPointer<Item>& n, int h)const {
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
template<class Data>
void RBTree<Data>::show() const {
    inorderTreeWalk(root);
    std::cout<<"************\n";
}
/************************************************************/

/*******
**  Item
**/
template <class Data>
RBTree<Data>::Item::~Item(){
    if(p){
        if(p->l == this) p->l = 0;
        else p->r = 0;
    }

    if(l) delete &l;
    if(r) delete &r;
    p = l = r = 0;
}

template<class Data>
RBTree<Data>::Item::Item(const Item& i){
    key = i.key;
    red = i.red;
    l = i.l;
    r = i.r;
    p = i.p;
}
/************************************************************/
/*class RBTree
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
};*/

};

#endif // RBTREE_H
