#ifndef RBNODE_H
#define RBNODE_H

namespace rbt{

struct Node {
    int key;
    bool red;
    Node *l, *r, *p;

    Node(int key): key(key), l(0), r(0), p(0), red(false) {}
    ~Node();
};

}

#endif // RBNODE_H
