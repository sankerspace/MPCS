
#include "Graph.hpp"
#include <iostream>



using  namespace std;

#ifdef __cplusplus__

  #include <iostream>
  #include <string>

  void ClearScreen()
    {
    cout << string( 100, '\n' );
    }

#else

  #include <stdio.h>

  void ClearScreen()
    {
    int n;
    for (n = 0; n < 10; n++)
      printf( "\n\n\n\n\n\n\n\n\n\n" );
    }

#endif 





int main(int argc,char** argv) {
	
	bool state=true;
	Graph g;
	while(state)
	{
	    char c;
	     //ClearScreen();
	    std::cout<<"Modify Graph with following options:"<< std::endl;
	    std::cout<<"----------------------------------"<< std::endl;
	    std::cout<<"new (n)ode"<< std::endl;
	    std::cout<<"new (e)dge"<< std::endl;
	    std::cout<<"(p)rint Graph"<< std::endl;
	    std::cout<<"(f)ind Circles"<< std::endl;
	    std::cout<<"(c)lose Program"<< std::endl;
	   
	   cin >> c;
	   switch(c)
	   {
	    case 'n':
	        g.addNode();
	        std::cout<<"\tNew Node created,number of nodes are "<< g.getNodeNumber()<< " [ENTER]"<<std::endl;
	        cin.get();
	        break;
	    case 'e':
	        int src,dst,value;
	        std::cout<<"\tEnter src node:";std::cin>>src;std::cout<<endl;
	        std::cout<<"\tEnter dst node:";std::cin>>dst;std::cout<<endl;
	        std::cout<<"\tEnter edge value:";std::cin>>value;std::cout<<endl;
	        g.addEdge((src-1),(dst-1),value);
	        std::cout<<"\tNew Edge created,number of edges are "<< g.getEdgeNumber()<< " [ENTER]"<<std::endl;
	        cin.get();
	        break;
	    
	    case 'p':
	         g.printGraph();
	         std::cout<<std::endl<<"[ENTER]"<<std::endl;
	         cin.get();
	        break;
	        
	    case 'f':
	        {
	        int edge_value=0;
	        bool ret=false;
	        std::cout<<"\tEnter defined weight for all edges:";
	        std::cin>>edge_value;
	        std::cout<<endl;
	        ret=g.findCircles(edge_value);
	        if(ret)
	        {
	           std::cout<<"FOUND CIRCLE!!"<<std::endl;
	        }else{
	           std::cout<<"No circle found!!"<<std::endl;
	        }
	        std::cout<<std::endl<<"[ENTER]"<<std::endl;
	        cin.get();
	        }
	        break;
	        
	    case 'c':
	         state=false;
	        break;
	    default:
	        break;
	   } 
	
	}
  
  	return 0;
}
