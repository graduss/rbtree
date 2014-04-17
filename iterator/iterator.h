#include <iterator>

#ifndef ITERATOR_H
#define ITERATOR_H

namespace rbt{

class RBTreeException;
class RBTree;

class Iterator : public std::iterator<std::input_iterator_tag, int>
{
    public:
        enum label{NOT_INIT, VALID, END};
        Iterator(): value(0), tree(0), state(NOT_INIT) {};
        Iterator(int x, const RBTree* t);
        Iterator(label _end, const RBTree* t): value(0), tree(t), state(_end) {}
        Iterator(const Iterator& mit): value(mit.value), tree(mit.tree), state(mit.state) {}
        Iterator& operator=(const Iterator& mit);

        Iterator& operator++();
        Iterator operator++(int);
        bool operator==(const Iterator& rhs) const;
        bool operator!=(const Iterator& rhs) const;
        int operator*() const;
    private:
        int value;
        const RBTree* tree;
        label state;
};

}
#endif // ITERATOR_H
