#include "RBTree.h"

namespace rbt{

class RBTree::Private{
    public:

    Private(): root(0) {}
    ~Private();
    struct Item{
        int key;
        bool red;
        SPointer<Item> l, r, p;

        Item(int k): key(k), red(false), l(0), r(0), p(0) {}
        Item(const Item& i);
        Item(): key(0), l(0), r(0), p(0) {}
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

    SPointer<Item> search(int key, SPointer<Item> root) const;

    /******* testing ***********/
    void inorderTreeWalk(const SPointer<Item>& n, int h = 0)const;
};

RBTree::~RBTree(){
    if(p) {
        delete p;
        p = 0;
    }
}

RBTree& RBTree::add(int key){
    if(!p) {
        p = new Private;
        if(!p) throw RBTreeException(RBTreeException::MEMORY_FAIL);
    }
    SPointer<Private::Item> n = new Private::Item(key);
    if(!n) throw RBTreeException(RBTreeException::MEMORY_FAIL);
    p->insert(n);
    return *this;
}

RBTree& RBTree::del(int key){
    if(!p) throw RBTreeException(RBTreeException::IS_EMPTY);

    SPointer<Private::Item> node = p->search(key, p->root);
    if(!node) throw RBTreeException(RBTreeException::NOT_FOUND);
    p->remove(node);

    return *this;
}

int RBTree::successor(int key) const {
    if(!p) throw RBTreeException(RBTreeException::IS_EMPTY);

    SPointer<Private::Item> node = p->search(key, p->root);
    if(!node) throw RBTreeException(RBTreeException::NOT_FOUND);
    else {
        SPointer<Private::Item> sucnode = p->_successor(node);
        if(!sucnode) throw RBTreeException(RBTreeException::IS_EXTRIM);
        else return sucnode->key;
    }
}

int RBTree::predecessor(int key) const {
    if(!p) throw RBTreeException(RBTreeException::IS_EMPTY);

    SPointer<Private::Item> node = p->search(key, p->root);
    if(!node) throw RBTreeException(RBTreeException::NOT_FOUND);
    else {
        SPointer<Private::Item> psucnode = p->_predecessor(node);
        if(!psucnode) throw RBTreeException(RBTreeException::IS_EXTRIM);
        else return psucnode->key;
    }
}

int RBTree::max() const {
    if(!p || !p->root) throw RBTreeException(RBTreeException::IS_EMPTY);
    else return p->_max(p->root)->key;
}

int RBTree::min() const {
    if(!p || !p->root) throw RBTreeException(RBTreeException::IS_EMPTY);
    else return p->_min(p->root)->key;
}

Iterator RBTree::begin() const {
    if(!p) throw RBTreeException(RBTreeException::IS_EMPTY);

    if(p->root) return Iterator(this->min(),this);
    else return Iterator(Iterator::END,this);
}

Iterator RBTree::end() const {
    return Iterator(Iterator::END,this);
}

bool RBTree::isThere(int key) const {
    if(!p) throw RBTreeException(RBTreeException::IS_EMPTY);

    return (bool)p->search(key, p->root);
}

/********** testing **************/
void RBTree::show() const {
    p->inorderTreeWalk(p->root);
    std::cout<<"************\n";
}

/********
* private
*/


RBTree::Private::~Private(){
    if(root) root = 0;
}

void RBTree::Private::leftRotate(SPointer<Private::Item> x){
    SPointer<Private::Item> y = x->r;

    x->r = y->l;
    if(y->l) y->l->p = x;

    y->p = x->p;

    if(!x->p) root = y;
    else if(x == x->p->l) x->p->l = y;
    else x->p->r = y;

    y->l = x;
    x->p = y;
}

void RBTree::Private::rightRotate(SPointer<Private::Item> x){
    SPointer<Private::Item> y = x->l;

    x->l = y->r;
    if(y->r) y->r->p = x;

    y->p = x->p;

    if(!x->p) root = y;
    else if(x == x->p->l) x->p->l = y;
    else x->p->r = y;

    y->r = x;
    x->p = y;
}

void RBTree::Private::btInsert(SPointer<Private::Item> n){
    SPointer<Private::Item> root = this->root;
    SPointer<Private::Item> x;

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

void RBTree::Private::insert(SPointer<Private::Item> x){
    btInsert(x);
    x->red = true;

    SPointer<Private::Item> y;
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

void RBTree::Private::remove(SPointer<Private::Item> node){
    SPointer<Private::Item> x, y;
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

void RBTree::Private::rmoveFixup(SPointer<Private::Item> x){
    SPointer<Private::Item> w;

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

SPointer<RBTree::Private::Item> RBTree::Private::_max(const SPointer<Private::Item> root) const {
    SPointer<Private::Item> n = root;

    while(n->r){
        n = n->r;
    }

    return n;
}

SPointer<RBTree::Private::Item> RBTree::Private::_min(const SPointer<Private::Item> root) const {
    SPointer<Private::Item> n = root;

    while(n->l){
        n = n->l;
    }

    return n;
}

SPointer<RBTree::Private::Item> RBTree::Private::_predecessor(SPointer<Private::Item> node) const {
    SPointer<Private::Item> ans;

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

SPointer<RBTree::Private::Item> RBTree::Private::_successor(SPointer<Private::Item> node) const {
    SPointer<Private::Item> ans;

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

SPointer<RBTree::Private::Item> RBTree::Private::search(int key, SPointer<Private::Item> root) const {
    if(!root || key == root->key) return root;
    else if (key < root->key) return search(key, root->l);
    else return search(key, root->r);
}

/**************** testting **********************************/
void RBTree::Private::inorderTreeWalk(const SPointer<Private::Item>& n, int h) const {
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

/*******
**  Item
**/
RBTree::Private::Item::~Item(){
    if(p){
        if(p->l == this) p->l = 0;
        else if(p->r == this) p->r = 0;
    }

    p = l = r = 0;
    red = false;
    key = 0;
}

RBTree::Private::Item::Item(const Item& i){
    key = i.key;
    red = i.red;
    l = i.l;
    r = i.r;
    p = i.p;
}

};
