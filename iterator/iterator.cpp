#include "../exceptions/RBTreeException.h"
#include "../RBTree.h"
#include "iterator.h"

namespace rbt{

int Iterator::operator*() const{
    if(state == VALID) return value;
    else throw RBTreeException(RBTreeException::IS_EXTRIM);
}

bool Iterator::operator==(const Iterator& rhs) const {
    if ( tree && rhs.tree && (tree == rhs.tree) ) {
        if (value == 0 && rhs.value == 0) {
            if(state == rhs.state) return true;
            else return false;
        }else if (value == rhs.value) return true;
        else return false;
    }else if(tree == rhs.tree) return true;
    else return false;
}

bool Iterator::operator!=(const Iterator& rhs) const {
    return !(*this == rhs);
}

Iterator& Iterator::operator++(){
    if (state == END) throw RBTreeException(RBTreeException::IS_EXTRIM);

    try{
        value = tree->successor(value);
    }catch(RBTreeException e){
        if (e.getType() == RBTreeException::IS_EXTRIM){
            value = 0;
            state = END;
        }else throw e;
    }

    return *this;
}

Iterator Iterator::operator++(int){
    Iterator old = *this;
    ++(*this);
    return old;
}

Iterator& Iterator::operator=(const Iterator& rhs){
    value = rhs.value;
    tree = rhs.tree;
    state = rhs.state;

    return *this;
}

Iterator::Iterator(int x, const RBTree* t){
    if (t->isThere(x)){
        value = x;
        tree = t;
        state = VALID;
    }else {
        tree = 0;
        value = 0;
        state = NOT_INIT;
    }
}

};
