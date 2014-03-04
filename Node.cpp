#include "Node.h"

namespace rbt {

Node::Node(const Node &n){
    key = n.key;
    l = n.l;
    r = n.r;
    p = n.p;
    red = n.red;
}

Node::~Node(){
    key = 0;
    red = false;

    if(l) delete l;
    if(r) delete r;
    if(p) {
        if(p->l == this) p->l = 0;
        else p->r = 0;
    }

    l = r = p = 0;
}

}
