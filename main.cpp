#include "RBTree.h"

using namespace rbt;

int main()
{
    RBTree<int> rb;
    rb.add(11).add(14).add(15).add(4).add(7).add(25).add(2).add(5).show();
    //rb.add(11).show();
    std::cout<<rb.min()<<"\n";
    std::cout<<rb.max()<<"\n";
    std::cout<<rb.successor(5)<<"\n";
    std::cout<<rb.predecessor(11)<<"\n";
    /*rb.del(2).show();*/
    std::cout<<"\n finish \n";
    return 0;
}
