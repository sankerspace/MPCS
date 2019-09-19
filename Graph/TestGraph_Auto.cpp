

#include "Graph.hpp"
#include <iostream>
#include "boost/filesystem.hpp"
#include "boost/filesystem/fstream.hpp"		
#include <boost/algorithm/string.hpp> 
#include <iostream>



using  namespace std;

namespace fs=boost::filesystem;

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
    std::string line;
    std::string f;
	std::cout<<"Filename: ";std::cin>>f;
	fs::path p{f.c_str() };
	if (!exists(p))    // does path p actually exist?
	{
		std::cout<< "ERROR::File doesnt exist!"<<std::endl;
		return -1 ;
	}
		
		
	fs::ifstream ifs{ p };
	
	while(std::getline(ifs,line))
	{
		/* 
		   node
		   edge x y w
		   print graph
		   print table
		   mode
		   find w
		   close
		*/
		std::vector<std::string> token;
		boost::split(token,line , boost::is_any_of(" ")); 		
		std::vector<std::string>::size_type len=token.size();
		if(len==1)
		{
			string str = token[0];
			if(str.compare("node"))
			{
				g.addNode();
				std::cout<<"Added a new node. Current Number of Nodes "<<g.getNodeNumber() <<std::endl;

			}else if(str.compare("undirected"))
			{
				g.setUndirectedMode();
				std::cout<<"Set to Undirected Mode. "<<std::endl;

			}else if(str.compare("close"))
			{
				break;	
			}
		}else if (len==2)
		{
			if(token[0].compare("print"))	
			{
				if(token[1].compare("graph"))
				{
					g.printGraph();
				}else if(token[1].compare("table"))
				{
					g.printTable();
				}	
			}else if(token[0].compare("find"))
			{
				std::stringstream ss(token[1]);
				int w=0;
				ss>>w;
			
			}
		}else if(len==3)
		{
		
		}

	
//	   cin >> c;

	}  
  	return 0;
}
