#include "SPointerException.h"

#ifndef SPOINTER_H
#define SPOINTER_H

namespace rbt{

template <class T>
class SPointer
{
    public:
        SPointer(): refPtr(0) {}
        SPointer(T* ptr);
        SPointer(const SPointer& s);
        virtual ~SPointer();

        SPointer& operator=(const SPointer& s);
        SPointer& operator=(T* ptr);

        T* operator->() const;
        T& operator*() const;
        operator bool() const;
        bool operator==(const SPointer& rv) const;
        bool operator!=(const SPointer& rv) const;
        bool operator==(const T* rv) const;
        bool operator!=(const T* rv) const;

        int get() const;
    private:
        struct Ref {
            T* realPtr;
            int counter;
        } *refPtr;
};

template <class T>
SPointer<T>::SPointer(T* ptr){
    if(ptr){
        refPtr = new Ref;
        if (!refPtr) throw SPointerException(SPointerException::MEMORY_FAIL);
        refPtr->realPtr = ptr;
        refPtr->counter = 1;
    }else{
        refPtr = 0;
    }
}

template <class T>
SPointer<T>::~SPointer() {
    if(refPtr){
        refPtr->counter--;
        if(refPtr->counter == 0){
            delete refPtr->realPtr;
            delete refPtr;
            refPtr = 0;
        }
    }
    refPtr = 0;
}

template<class T>
T* SPointer<T>::operator->() const {
    if(refPtr) return refPtr->realPtr;
    else return 0;
}

template<class T>
SPointer<T>& SPointer<T>::operator=(const SPointer& orig){
    if(refPtr == orig.refPtr) return *this;
    else if(refPtr){
        refPtr->counter--;
        if(refPtr->counter == 0){
            delete refPtr->realPtr;
            delete refPtr;
            refPtr = 0;
        }
    }
    refPtr = orig.refPtr;
    if(refPtr) refPtr->counter++;
    return *this;
}

template<class T>
T& SPointer<T>::operator*() const {
    if(refPtr) return *refPtr->realPtr;
    else throw SPointerException(SPointerException::BAD_POINTER);;
}

template<class T>
SPointer<T>::SPointer(const SPointer& orig):refPtr(orig.refPtr) {
    if(refPtr) refPtr->counter++;
}

template<class T>
SPointer<T>& SPointer<T>::operator=(T* ptr){
    if(refPtr){
        refPtr->counter--;
        if(refPtr->counter == 0){
            delete refPtr->realPtr;
            delete refPtr;
            refPtr = 0;
        }
    }

    if(ptr){
        refPtr = new Ref;
        if (!refPtr) throw SPointerException(SPointerException::MEMORY_FAIL);
        refPtr->realPtr = ptr;
        refPtr->counter = 1;
    }else{
        refPtr = 0;
    }

    return *this;
}

template<class T>
SPointer<T>::operator bool() const {
    if(refPtr) return true;
    else return false;
}

template<class T>
bool SPointer<T>::operator==(const SPointer<T>& rv) const {
    if(refPtr == rv.refPtr) return true;
    else return false;
}

template<class T>
bool SPointer<T>::operator!=(const SPointer<T>& rv) const {
    return !(*this == rv);
}

template<class T>
bool SPointer<T>::operator==(const T* rv) const {
    if((!refPtr || !refPtr->realPtr) && !rv) return true;
    else if(refPtr && (refPtr->realPtr == rv)) return true;
    else return false;
}

template<class T>
bool SPointer<T>::operator!=(const T* rv) const {
    return !(*this == rv);
}
/************  testing  *************/
template<class Data>
int SPointer<Data>::get() const {
    if(refPtr) return refPtr->counter;
    else return 0;
}

};
#endif // SPOINTER_H
