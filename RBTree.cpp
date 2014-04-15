#include "RBTree.h"
#include "smartpointer/SPointer.h"

namespace rbt{

template<typename Data>
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
};

template<class Data>
RBTree<Data>::Private::~Private(){
    if(root) root = 0;
}

/*******
**  Item
**/
template <class Data>
RBTree<Data>::Private::Item::Item(){
    red = false;
    l = r = p = 0;
}

template <class Data>
RBTree<Data>::Private::Item::~Item(){
    if(p){
        if(p->l == this) p->l = 0;
        else if(p->r == this) p->r = 0;
    }

    p = l = r = 0;
    red = false;
    key = 0;
}

template<class Data>
RBTree<Data>::Private::Item::Item(const Item& i){
    key = i.key;
    red = i.red;
    l = i.l;
    r = i.r;
    p = i.p;
}
};
