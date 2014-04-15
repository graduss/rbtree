#include <stdexcept>

#ifndef SPOINTEREXCEPTION_H
#define SPOINTEREXCEPTION_H

namespace rbt{

class SPointerException : public std::exception
{
    public:
        enum e_types {MEMORY_FAIL, BAD_POINTER};

        SPointerException(const e_types t): type(t) {};
        SPointerException(const SPointerException& el);
        SPointerException& operator=(const SPointerException& el);
        virtual const char* what() const throw();
    private:
        e_types type;
};

}

#endif // SPOINTEREXCEPTION_H
