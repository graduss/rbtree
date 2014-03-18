#include "RBTree.h"

using namespace rbt;

int main()
{
    RBTree<int> rb;
    rb.add(11).add(14).add(15).add(4).add(7).add(1).add(2).add(8).add(5).add(4).show();
    /*rb.del(2).show();*/
    std::cout<<"\n finish \n";
    return 0;
}
