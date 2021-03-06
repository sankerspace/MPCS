
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

  #include <cstdio>



  void ClearScreen()
    {
    int n;
    for (n = 0; n < 5; n++)
      printf( "\n\n\n\n\n\n\n\n\n\n" );
    }

#endif 





int main(int argc,char** argv) {
	
	bool state=true;
	Graph g;
	while(state)
	{
	    char c;
	     ClearScreen();
	    std::cout<<"Modify Graph with following options:"<< std::endl;
	    std::cout<<"----------------------------------"<< std::endl;
	    std::cout<<"new (n)ode"<< std::endl;
	    std::cout<<"new (e)dge"<< std::endl;
	    std::cout<<"(p)rint Graph"<< std::endl;
	    std::cout<<"print (t)able"<< std::endl;
	    std::cout<<"(f)ind Circles"<< std::endl;
	    std::cout<<"(m)ode change"<< std::endl;
	    std::cout<<"(c)lose Program"<< std::endl;
		std::cout <<std::endl<<std::endl<<std::endl;   
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
	    
	    case 't':
	         g.printTable();
	         std::cout<<std::endl<<"[ENTER]"<<std::endl;
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
			std::cout<<"\tSearch for cycles in the current defined Graph."<<std::endl;
	        std::cout<<"\tCycles are searched explicit on edges wit specified edge value."<<std::endl;
	        std::cout<<"\tEnter defined weight for all edges:[0 ignore edge values]"<<std::endl;
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
	        
	    case 'm':
	         std::cout<<std::endl<<"Changing Mode..... "<<std::endl;
			 if(g.getMode()){
				 g.setUndirectedMode();
				 std::cout<<std::endl<<"Graph in UNDIRECTED Mode now."<<std::endl;
			 }else{
				// g.setDirectedMode();
				 std::cout<<std::endl<<"Graph in UNDIRECTED Mode now.Change to DIRTECTED Mode not allowed"<<std::endl;
			 }
			 std::cout<<std::endl<<"[ENTER]"<<std::endl;
	         cin.get();
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
