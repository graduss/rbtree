#include <iostream>
#include "smartpointer/SPointer.h"

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

private:
    struct Item{
        Data key;
        SPointer<Item> l, r, p;

        Item(Data& k): key(k), l(0), r(0), p(0) {}
        ~Item();
    };
    SPointer<Item> root;
};

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
