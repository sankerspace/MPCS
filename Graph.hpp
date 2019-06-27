#ifndef _GRAPH_HEADER_
#define _GRAPH_HEADER_

#include <iostream>
#include <vector>

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

    std::vector<std::vector<std::pair<int,int>>> adjList;
    int N,E;
    
    /*recursively search for path and mark as visited */
    /*if during search we found  a already marked one, return true*/
    bool dsv(int node,int value, std::vector<bool>& visited,std::vector<bool>& finished,std::vector<int>& found);
public:
	// construct a vector of vectors to represent an adjacency list
	//one vector represents to a node connected other  nodes with id (int) and 
	//edge has a value (int)
	

    // Standard Graph Constructor
    Graph() 
    {
        N=0;
        E=0;
    };
    
	// Graph Constructor
	//# of nodes = N
	Graph(std::vector<Edge> const &edges, int N)
	{
		// resize the vector to N elements of type vector<int>
		adjList.resize(N);
        this->N=N;
		// add edges to the directed graph
		for (auto &edge: edges)
		{
		    std::pair<int,int> pair(edge.dest,edge.value);
			// insert at the end
			//adjList[edge.src].push_back(edge.dest);
            adjList[edge.src].push_back(pair);
             this->E++;

			// Uncomment below line for undirected graph
			// adjList[edge.dest].push_back(edge.src);
		}
	};
	
	
	int getNodeNumber(void);
	int getEdgeNumber(void);	
	int addNode(void); //returns actual number of nodes = index of new node
	int addEdge(int src,int dst,int value);	
    void printGraph(void);
    
    /*find cricles from every node,but restricted on edges with value edge_value*/
    /*an edge_value of zero means, no restriction*/
    bool findCircles(int edge_value);
};





#endif
