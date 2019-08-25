#ifndef _GRAPH_HEADER_
#define _GRAPH_HEADER_

#include <iostream>
#include <vector>
#include <boost/filesystem.hpp>


#define dbg_graph_getNodeNumber
#define dbg_graph_findcircle

// data structure to store graph edges
struct Edge {
	int src, dest,value;
	
};

// class to represent a graph object
class Graph
{
private:
	
		
	typedef std::pair<std::pair<int,int>,bool> Pair_PairofInt_Bool;
	std::vector<std::vector<Pair_PairofInt_Bool>> adjList;

    int N,E_undirect; //number of nodes N,edges E
	/*mode of the graph - directed or undirected
	*  - directed: every occurence in the vector handled "as one direction"
	*  - undirected: ever occurence in the vector handled as a connection(in both ways)
	*  - 			 if changed from directed mode, only first occurence of a connection relevant
	*/	
    bool directed;
    /*recursively search for path and mark as visited */
    /*if during search we found  a already marked one, return true*/
	/*XXXXXXXXXXXXXXXXXXXXcheck itXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXx*/
	
	void insert_Pair_to_Vector(int index,Pair_PairofInt_Bool p);
    bool dsv(int node,int value, std::vector<bool>& visited,std::vector<bool>& finished,std::vector<int>& found,int root);
	public:
	// construct a vector of vectors to represent an adjacency list
	//one vector represents the to a corresponding node adjacent nodes with an id (integer) and 
	//edge has a value (int)
		

    // Standard Graph Constructor
    Graph(bool directed=true) 
    {
        N=0;
        E_undirect=0;
		this->directed=directed;
    };
    
	/*XXXXXXXXXXXXXXXXXXXXXXXXX TEST XXXXXXXXXXXXXXXXXXXXXXXXXX*/
	// Graph Constructor
	//# of nodes = N
/*	Graph(std::vector<Edge> const &edges, int N,bool directed=true)
	{
		this->directed=directed;
		// resize the vector to N elements of type vector<int>
		adjList.resize(N);
        this->N=N;
		// add edges to the directed graph
		for (auto &edge: edges)
		{
		    std::pair<int,int> pair_1(edge.dest,edge.value);
		    std::pair<std::pair<int,int>, bool> pair_2(pair_1,true);
            
		    std::pair<int,int> pair_3(edge.src,edge.value);
		    std::pair<std::pair<int,int>, bool> pair_4(pair_3,false);
			if(directed)
			{
				// insert at the end
				//adjList[edge.src].push_back(edge.dest);
				adjList[edge.src].push_back(pair);//have to be sorted!!!!!!!!!!!!!!

				this->E++;

			
			}else
			{
			
			}
			// Uncomment below line for undirected graph
			// adjList[edge.dest].push_back(edge.src);
		}
	};*/
	
	
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
	bool setDirectedMode(void); //interpret edges as directed
	bool setUndirectedMode(void); //interpret edges as undirected
};



#endif
