#include "RBTree.h"

using namespace rbt;

int main()
{
    try{
        RBTree rb;
        //RBTree<double> rbd;

        std::cout<<"\n*** add ****\n";
        rb.add(11).add(14).add(15).add(4).add(7).add(25).add(5).show();
        //rb.add(11).show();
        std::cout<<"min:\t\t"<<rb.min()<<"\n";
        std::cout<<"max:\t\t"<<rb.max()<<"\n";
        std::cout<<"5 succes.:\t"<<rb.successor(5)<<"\n";
        std::cout<<"11 predec.:\t"<<rb.predecessor(11)<<"\n";
        std::cout<<"***** del ******\n";
        //rb.show();
        rb.del(4).del(7).show();

        std::cout<<"\n*** iterator ****\n";
        Iterator start = rb.begin();
        while(start != rb.end()){
            std::cout<<*(start++)<<"\n";
        }

        std::cout<<"\n finish \n";
    }catch(std::exception& e){
        std::cout<<e.what()<<"\n";
    }

    return 0;
}
