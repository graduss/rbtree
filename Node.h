#ifndef RBNODE_H
#define RBNODE_H

namespace rbt{

struct Node {
    int key;
    bool red;
    Node *l, *r, *p;

    Node(int key): key(key), red(false), l(0), r(0), p(0) {}
    Node(): key(0), red(false), l(0), r(0), p(0) {}
    Node(const Node &n);
    ~Node();
};

}

#endif // RBNODE_H
