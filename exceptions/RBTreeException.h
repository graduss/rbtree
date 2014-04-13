#include <stdexcept>

#ifndef RBTREEEXCEPTION_H
#define RBTREEEXCEPTION_H

namespace rbt{

class RBTreeException : public std::exception
{
    public:
        enum e_types {NOT_FOUND, MEMORY_FAIL, IS_EMPTY, IS_EXTRIM};

        RBTreeException(const e_types t): type(t) {}
        RBTreeException(const RBTreeException& e);
        RBTreeException& operator=(const RBTreeException& e);
        virtual const char* what() const throw();
        virtual const e_types getType() const;
        //virtual ~RBTreeException();
    private:
        e_types type;
};

}

#endif // RBTREEEXCEPTION_H
