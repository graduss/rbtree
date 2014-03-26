#include "RBTree.h"

using namespace rbt;

int main()
{
    RBTree<int> rb;
    RBTree<double> rbd;

    std::cout<<"\n*** int ****\n";
    rb.add(11).add(14).add(15).add(4).add(7).add(25).add(5).show();
    //rb.add(11).show();
    std::cout<<"min:\t"<<rb.min()<<"\n";
    std::cout<<"max:\t"<<rb.max()<<"\n";
    std::cout<<"5 succes.:\t"<<rb.successor(5)<<"\n";
    std::cout<<"11 predec.:\t"<<rb.predecessor(11)<<"\n";
    std::cout<<"***************\n";
    //rb.show();
    rb.del(4).del(7).show();

    std::cout<<"\n*** double ****\n";
    rbd.add(1.5).add(0.7).add(12.5).add(1.258).add(12.465).add(25.4).add(14.23).add(13.565).add(15).show();
    rbd.del(0.7).show();

    std::cout<<"\n finish \n";

    return 0;
}
