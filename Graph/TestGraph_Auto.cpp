

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

bool is_number(const std::string &s) {
  return !s.empty() && std::all_of(s.begin(), s.end(), ::isdigit);
}


int main(int argc,char** argv) {
	try
	{
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
			   undirected
			   find circle w
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
				} 
			}else if(len==3)
			{
				if(token[0].compare("find") && token[1].compare("circle") && is_number(token[2]))
				{
					std::stringstream ss(token[1]);
					int w=0;
					ss>>w;
					if(ss.fail())
					{
						std::cout<<"ERROR::Reading number from string failed!"<<std::endl;
					}
					std::cout<<"Find a circle in "<<(g.getMode()?"directed":"undirected") <<" Graph."<<std::endl;
					g.findCircles(w);		
				}

			}else if(len==4)
			{

				if(token[0].compare("edge") &&  is_number(token[1]) && is_number(token[2]) &&  is_number(token[3]))
				{
					int s1=std::stoi(token[1]);
					int s2=std::stoi(token[2]);
					int s3=std::stoi(token[3]);

					std::cout<<"Inserting a new EDGE from Node "<<s1<< " to Node "<<s2<< "with weight "<<s3<< std::endl;
					g.addEdge(s1,s2,s3);
				}		 

			}
		}  
	}catch(exception& e)
	{
		std::cout<<"ERROR::Exception happend!"<<std::endl;
		std::cout<<"\t"<<e.what()<<std::endl;

	}catch(...)
	{
		std::cout<<"ERROR::Unknown Exception happend!"<<std::endl;
	}

		return 0;
}
