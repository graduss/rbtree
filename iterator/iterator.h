#include <iterator>

#ifndef ITERATOR_H
#define ITERATOR_H

namespace rbt{

template <class Data> class RBTree;
class RBTreeException;

template<class Data>
class Iterator : public std::iterator<std::input_iterator_tag, Data>
{
    public:
        enum label{NOT_INIT, VALID, END};
        Iterator(): value(0), tree(0), state(NOT_INIT) {};
        Iterator(const Data& x, const RBTree<Data>* t);
        Iterator(label _end, const RBTree<Data>* t): value(0), tree(t), state(_end) {}
        Iterator(const Iterator& mit): value(mit.value), tree(mit.tree), state(mit.state) {}
        Iterator& operator=(const Iterator& mit);

        Iterator& operator++();
        Iterator operator++(int);
        bool operator==(const Iterator& rhs) const;
        bool operator!=(const Iterator& rhs) const;
        const Data& operator*() const;
    private:
        const Data* value;
        const RBTree<Data>* tree;
        label state;
};

template<class Data>
const Data& Iterator<Data>::operator*() const{
    if(state == VALID) return *value;
    else throw RBTreeException(RBTreeException::IS_EXTRIM);
}

template<class Data>
bool Iterator<Data>::operator==(const Iterator& rhs) const {
    if ( tree && rhs.tree && (tree == rhs.tree) ) {
        if (value == 0 && rhs.value == 0) {
            if(state == rhs.state) return true;
            else return false;
        }else if (value == rhs.value) return true;
        else return false;
    }else if(tree == rhs.tree) return true;
    else return false;
}

template<class Data>
bool Iterator<Data>::operator!=(const Iterator& rhs) const {
    return !(*this == rhs);
}

template<class Data>
Iterator<Data>& Iterator<Data>::operator++(){
    if (state == END) throw RBTreeException(RBTreeException::IS_EXTRIM);

    try{
        value = &(tree->successor(*value));
    }catch(RBTreeException e){
        if (e.getType() == RBTreeException::IS_EXTRIM){
            value = 0;
            state = END;
        }else throw e;
    }

    return *this;
}

template<class Data>
Iterator<Data> Iterator<Data>::operator++(int){
    Iterator old = *this;
    ++(*this);
    return old;
}

template<class Data>
Iterator<Data>& Iterator<Data>::operator=(const Iterator& rhs){
    value = rhs.value;
    tree = rhs.tree;
    state = rhs.state;

    return *this;
}

template<class Data>
Iterator<Data>::Iterator(const Data& x, const RBTree<Data>* t){
    if (t->isThere(x)){
        value = &x;
        tree = t;
        state = VALID;
    }else {
        tree = 0;
        value = 0;
        state = NOT_INIT;
    }
}

}
#endif // ITERATOR_H
