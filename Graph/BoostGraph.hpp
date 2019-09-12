

#ifndef _BOOST_GRAPH_HEADER_
#define _BOOST_GRAPH_HEADER_

#include <iostream>
#include <vector>
#include <boost/filesystem.hpp>



class Graph
{
private:
	
		
	//typedef std::pair<std::pair<int,int>,bool> Pair_PairofInt_Bool;
	//std::vector<std::vector<Pair_PairofInt_Bool>> adjList;

    int N,E_undirect; //number of nodes N,edges E
   
   	bool directed;
    
	
   // bool dsv(int node,int value, std::vector<bool>& visited,std::vector<bool>& finished,std::vector<int>& found,int root);
	

public:
	// construct a vector of vectors to represent an adjacency list
	//one vector represents the to a corresponding node adjacent nodes with an id (integer) and 
	//edge has a value (int)
		

    // Standard Graph Constructor
    Graph() 
    {
        N=0;
        E_undirect=0;
		this->directed=directed;
    };
    
	
	int getNodeNumber(void);
	int getEdgeNumber(void);	
	int addNode(void); //returns actual number of nodes = index of new node
	int addEdge(int src,int dst,int value);//returns actual number of edges	
    void printGraph(void);
	void printTable(void);	
		
    /*find cricles from every node,but restricted on edges with value edge_value*/
    /*an edge_value of zero means, no restriction*/
    bool findCircles(int edge_value);

	bool getMode(void);
//	bool setDirectedMode(void); //interpret edges as directed
	bool setUndirectedMode(void); //interpret edges as undirected
};



#endif
