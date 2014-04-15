#include "SPointerException.h"

namespace rbt{

SPointerException::SPointerException(const SPointerException& sp) {
    type = sp.type;
}

SPointerException& SPointerException::operator=(const SPointerException& sp) {
    if(&sp == this) return *this;

    type = sp.type;
    return *this;
}

const char* SPointerException::what() const throw() {
    if(type == MEMORY_FAIL) return "Memory fail!";
    else if (type == BAD_POINTER) return "Bad pointer!";
    else return "SPointerException - Type Error!";
}

}
