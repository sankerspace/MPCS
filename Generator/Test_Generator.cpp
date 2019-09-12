

#include <iostream>
#include "MPC_Generator.hpp"


int main(int argc,char** argv)
{
    int n;
    std::cout<<"Number of Nodes:";
    std::cin>>n;
    std::cout<<std::endl;
    
    generate_MPC("./Generated.Examples.MPCs.txt",n);
    
    return 0;
}
