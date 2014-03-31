#include "RBTreeException.h"

namespace rbt{

RBTreeException::RBTreeException(const RBTreeException& e) {
    type = e.type;
}

RBTreeException& RBTreeException::operator=(const RBTreeException& e){
    if(this == &e) return *this;

    type = e.type;
    return *this;
}

const char* RBTreeException::what() const throw() {
    switch(type){
        case NOT_FOUND: return"Node not found!";
        case MEMORY_FAIL: return "Memory fail!";
        case IS_EMPTY: return "Tree is empty!";
        case IS_EXTRIM: return "The node is extrim!";
        default: return "Type Error!";
    }
}

}
