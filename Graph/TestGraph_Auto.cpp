

#include "Graph.hpp"
#include <iostream>
#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>		
#include <boost/algorithm/string.hpp> 
#include <sstream>



//using  namespace std;

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
		if(argc==2)
		{
			f=std::string(argv[1]);
		}else
		{
			std::cout<<"Filename: ";std::cin>>f;
		}
		fs::path p{f.c_str() };
		if (!fs::exists(p))    // does path p actually exist?
		{
			std::cout<< "ERROR::File doesnt exist!"<<std::endl;
			return -1 ;
		}
		int line_number=1;

		fs::ifstream ifs{ p };

		while(std::getline(ifs,line))
		{
			if (line[0]=='#') continue;

			//std::cout<<line<<" ";
			/* 
			   node
			   
			   edge x y w
			   print graph
			   print table
			   print number nodes
			   print number edges
			   undirected
			   find circle w
			   close
			   */
			bool valid=false;
			std::vector<std::string> token;
			boost::split(token,line , boost::is_any_of(" ")); 		
			std::vector<std::string>::size_type len=token.size();

			if(len==1)
			{
				std::string str = token[0];
				if(str.compare("node")==0)
				{
					g.addNode();
					std::cout<<"++Added a new node. Current Number of Nodes "<<g.getNodeNumber() <<"+++++++++++++"<<std::endl;	
					valid=true;
				}else if(str.compare("undirected")==0)
				{
					g.setUndirectedMode();
					std::cout<<"++Set to Undirected Mode. "<<std::endl;
					valid=true;

				}else if(str.compare("close")==0)
				{
					break;	
				}
			}else if (len==2)
			{
				if(token[0].compare("print")==0)	
				{
					if(token[1].compare("graph")==0)
					{
						g.printGraph();
						valid=true;
					}else if(token[1].compare("table")==0)
					{
						g.printTable();
						valid=true;
					}	
				} 
			}else if(len==3)
			{
				
				if(token[0].compare("print")==0)	
				{
					if(token[1].compare("number")==0)
					{
						if(token[2].compare("nodes")==0)
						{
							std::cout<<"++NUMBER OF NODES: "<<g.getNodeNumber()<<"+++++++"<<std::endl;
							valid=true;

						}	
						else if(token[2].compare("edges")==0)
						{
							std::cout<<"++NUMBER OF EDGES: "<<g.getEdgeNumber()<<"++++++++"<<std::endl;
							valid=true;
						}	
						
					}				} 
				if(token[0].compare("find")==0 && token[1].compare("circle")==0 && is_number(token[2]))
				{

					int w=std::stoi(token[2]);
					std::cout<<"+++Try to find a circle in "<<(g.getMode()?"directed":"undirected") <<" Graph with weight "<<w<<".++++"<<std::endl;
					bool ret=g.findCircles(w);		
					std::stringstream ss;
					ss<<"\tFOUND A CIRCLE in current Graph with weight "<<w<<"."; 
					std::cout<<(ret?(ss.str()) :"\tNO CIRCLE FOUND.")<<std::endl;
					valid=true;
				}

			}else if(len==4)
			{

				if(token[0].compare("edge")==0 &&  is_number(token[1]) && is_number(token[2]) &&  is_number(token[3]))
				{
					int s1=std::stoi(token[1])-1;
					int s2=std::stoi(token[2])-1;
					int s3=std::stoi(token[3]);
					if(s1>=0  && s2>=0 && s3>=0)
					{
					std::cout<<"++++Inserting a new EDGE from Node "<<s1+1<< " to Node "<<s2+1<< " with weight "<<s3<<"++++"<< std::endl;
						g.addEdge(s1,s2,s3);
						valid=true;
					}
				}		 

			}
			if(!valid)  std::cout<<"ERROR::Input  at line number "<<line_number<<" in file "<< f <<" is not valid."<<std::endl;
			line_number++;
		}  
	}catch(std::exception& e)
	{
		std::cout<<"ERROR::Exception happend!"<<std::endl;
		std::cout<<"\t"<<e.what()<<std::endl;

	}catch(...)
	{
		std::cout<<"ERROR::Unknown Exception happend!"<<std::endl;
	}
	std::cout<<std::endl;
	return 0;
}
