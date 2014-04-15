#include "smartpointer/SPointer.h"
#include "exceptions/RBTreeException.h"
#include "iterator/iterator.h"
#include <iostream>

#ifndef RBTREE_H
#define RBTREE_H

namespace rbt{

template <class Data>
class RBTree {

public:
    RBTree();
    ~RBTree();

    /*RBTree& add(const Data& key);
    RBTree& del(const Data& key);

    Data& successor(const Data& key) const;
    Data& predecessor(const Data& key) const;
    Data& min() const;
    Data& max() const;

    Iterator<Data> begin() const;
    Iterator<Data> end() const;

    bool isThere(const Data& key) const;*/

    /********** testing **************/
    void show() const;

private:
    class Private;
    Private *p;
    /*struct Item{
        Data key;
        bool red;
        SPointer<Item> l, r, p;

        Item(const Data& k): key(k), red(false), l(0), r(0), p(0) {}
        Item(const Item& i);
        Item();
        ~Item();
    };
    SPointer<Item> root;

    void leftRotate(SPointer<Item> x);
    void rightRotate(SPointer<Item> x);
    void btInsert(SPointer<Item> x);
    void insert(SPointer<Item> x);
    void remove(SPointer<Item> x);
    void rmoveFixup(SPointer<Item> node);

    SPointer<Item> _min(const SPointer<Item> root) const;
    SPointer<Item> _max(const SPointer<Item> root) const;
    SPointer<Item> _successor(SPointer<Item> node) const;
    SPointer<Item> _predecessor(SPointer<Item> node) const;

    SPointer<Item> search(const Data& key, SPointer<Item> root) const;*/

    /******* testing ***********/
    /*void inorderTreeWalk(const SPointer<Item>& n, int h = 0)const;*/
};

template<class Data>
RBTree<Data>::RBTree(){
    p = new Private();
    if(!p) throw "Init Error";
}

template<class Data>
RBTree<Data>::~RBTree(){
    if(p) delete p;
}
/*template<class Data>
class RBTree<Data>::Private{
    public:
    Private(): root(0) {}
    ~Private();
    struct Item{
        Data key;
        bool red;
        SPointer<Item> l, r, p;

        Item(const Data& k): key(k), red(false), l(0), r(0), p(0) {}
        Item(const Item& i);
        Item();
        ~Item();
    };
    SPointer<Item> root;
};*/
/*******
** RBTree
**/
/*template<class Data>
Iterator<Data> RBTree<Data>::begin() const {
    if(root) return Iterator<Data>(this->min(),this);
    else return Iterator<Data>(Iterator<Data>::END,this);
}

template<class Data>
Iterator<Data> RBTree<Data>::end() const {
    return Iterator<Data>(Iterator<Data>::END,this);
}

template<class Data>
bool RBTree<Data>::isThere(const Data& key) const {
    return (bool)search(key, root);
}

template<class Data>
RBTree<Data>& RBTree<Data>::del(const Data& key){
    SPointer<Item> node = search(key, root);
    if(!node) throw RBTreeException(RBTreeException::NOT_FOUND);
    remove(node);

    return *this;
}

template<class Data>
void RBTree<Data>::remove(SPointer<Item> node){
    SPointer<Item> x, y;
    bool imaginaryX = false;

    if(!node->l || !node->r) y = node;
    else y = _successor(node);

    if(y->l) x = y->l;
    else x = y->r;
    if(!x) {
        x = new Item;
        if(!x) throw RBTreeException(RBTreeException::MEMORY_FAIL);
        imaginaryX = true;
    }

    x->p = y->p;
    if(!y->p) root = x;
    else {
        if (y == y->p->l) y->p->l = x;
        else y->p->r = x;
    }

    if (y != node) node->key = y->key;

    if(!imaginaryX && !y->red) {
        rmoveFixup(x);
    }
    if (imaginaryX){
        if(x == x->p->l) x->p->l = 0;
        else x->p->r = 0;
        x = 0;
    }
}

template<class Data>
void RBTree<Data>::rmoveFixup(SPointer<Item> x){
    SPointer<Item> w;

    while (x != root && !x->red){
        if (x == x->p->l){
            w = x->p->r;
            if (w->red){ // случей 1 (I)
                w->red = false;
                w->p->red = true;
                leftRotate(x->p);
                w = x->p->r;
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
    x->red = false;
}

template<class Data>
Data& RBTree<Data>::max() const {
    if(!root) throw RBTreeException(RBTreeException::IS_EMPTY);
    else return _max(root)->key;
}

template<class Data>
Data& RBTree<Data>::min() const {
    if(!root) throw RBTreeException(RBTreeException::IS_EMPTY);
    else return _min(root)->key;
}

template<class Data>
Data& RBTree<Data>::successor(const Data& key) const {
    SPointer<Item> node = search(key, root);
    if(!node) throw RBTreeException(RBTreeException::NOT_FOUND);
    else {
        SPointer<Item> sucnode = _successor(node);
        if(!sucnode) throw RBTreeException(RBTreeException::IS_EXTRIM);
        else return sucnode->key;
    }
}

template<class Data>
Data& RBTree<Data>::predecessor(const Data& key) const {
    SPointer<Item> node = search(key, root);
    if(!node) throw RBTreeException(RBTreeException::NOT_FOUND);
    else {
        SPointer<Item> psucnode = _predecessor(node);
        if(!psucnode) throw RBTreeException(RBTreeException::IS_EXTRIM);
        else return psucnode->key;
    }
}

template<class Data>
SPointer<typename RBTree<Data>::Item> RBTree<Data>::_predecessor(SPointer<Item> node) const {
    SPointer<Item> ans;

    if(node->l){
        ans = _max(node->r);
    }else{
        ans = node->p;
        while(ans && node==ans->l){
            node = ans;
            ans = ans->p;
        }
    }

    return ans;
}

template<class Data>
SPointer<typename RBTree<Data>::Item> RBTree<Data>::_successor(SPointer<Item> node) const {
    SPointer<Item> ans;

    if(node->r){
        ans = _min(node->r);
    }else{
        ans = node->p;
        while(ans && node == ans->r){
            node = ans;
            ans = ans->p;
        }
    }

    return ans;
}

template<class Data>
SPointer<typename RBTree<Data>::Item> RBTree<Data>::_max(const SPointer<Item> root) const {
    SPointer<Item> n = root;

    while(n->r){
        n = n->r;
    }

    return n;
}

template<class Data>
SPointer<typename RBTree<Data>::Item> RBTree<Data>::_min(const SPointer<Item> root) const {
    SPointer<Item> n = root;

    while(n->l){
        n = n->l;
    }

    return n;
}

template<class Data>
SPointer<typename RBTree<Data>::Item> RBTree<Data>::search(const Data& key, SPointer<Item> root) const {
    if(!root || key == root->key) return root;
    else if (key < root->key) return search(key, root->l);
    else return search(key, root->r);
}

template<class Data>
RBTree<Data>& RBTree<Data>::add(const Data& key){
    SPointer<Item> n = new Item(key);
    if(!n) throw RBTreeException(RBTreeException::MEMORY_FAIL);
    insert(n);
    return *this;
}

template<class Data>
void RBTree<Data>::insert(SPointer<Item> x){
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
void RBTree<Data>::btInsert(SPointer<Item> n){
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
    if(root) root = 0;
}*/
/**************** testting **********************************/
/*template<class Data>
void RBTree<Data>::inorderTreeWalk(const SPointer<Item>& n, int h)const {
    if(n){
        inorderTreeWalk(n->l, h+1);
        for(int i = h; i>0; i--){
            std::cout<<"->";
        }
        std::cout<<n->key<<"\t"<<n.get()<<"\t";
        if(n->red) std::cout<<"red"<<std::endl;
        else std::cout<<"black"<<std::endl;
        inorderTreeWalk(n->r, h+1);
    }
}
template<class Data>
void RBTree<Data>::show() const {
    inorderTreeWalk(root);
    std::cout<<"************\n";
}*/
/************************************************************/

/*******
**  Item
**/
/*template<class Data>
RBTree<Data>::Item::Item(){
    red = false;
    l = r = p = 0;
}

template <class Data>
RBTree<Data>::Item::~Item(){
    if(p){
        if(p->l == this) p->l = 0;
        else if(p->r == this) p->r = 0;
    }

    p = l = r = 0;
    red = false;
    key = 0;
}

template<class Data>
RBTree<Data>::Item::Item(const Item& i){
    key = i.key;
    red = i.red;
    l = i.l;
    r = i.r;
    p = i.p;
}*/
/************************************************************/
};

#endif // RBTREE_H
