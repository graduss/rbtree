#include "Node.h"

namespace rbt {

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
