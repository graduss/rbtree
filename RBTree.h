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
        Item(const Item& i);
        ~Item();
    };
    SPointer<Item> root;

    void leftRotate(SPointer<Item>& x);
    void rightRotate(SPointer<Item>& x);
    SPointer<Item>& btInsert(SPointer<Item>& x);
};
/*******
** RBTree
**/
template<class Data>
SPointer<typename RBTree<Data>::Item>& RBTree<Data>::btInsert(SPointer<Item>& n){
    SPointer<Item> root = this->root;
    SPointer<Item>& x;

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

template<class Data>
void RBTree<Data>::leftRotate(SPointer<Item>& x){
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
void RBTree<Data>::rightRotate(SPointer<Item>& x){
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
