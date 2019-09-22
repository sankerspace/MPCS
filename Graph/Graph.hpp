/*
 *AUTHOR : Marko Stanisic
 *CONTACT: e0325230@student.tuwien.ac.at
 *
 *
 *
 *
 * */
#ifndef _GRAPH_HEADER_
#define _GRAPH_HEADER_

#include <iostream>
#include <vector>
#include <boost/filesystem.hpp>


//#define dbg_graph_getNodeNumber
//#define dbg_graph_findcircle

// data structure to store graph edges
struct Edge {
	int src, dest,value;
	
};


// class to represent a graph object
/*********************************************************************************************************
 *Graph Properties:
 *	1) Graph can be directed(from start) or undirected(switched), 
 *		a)Graph initiates only as directed
 *		b)Graph can be switched to undirected but not vice versa
 *		c)Graph is build by an adjacent list,every node stores outgoing edges to another nodes
 *	2)Every edge  must have a weight value
 *		a)
 *	3)Undirected Edges are two directed edges in both ways, with the same weight
 *  4)Directed Edges are defined by an entry in a vector(describes outer edges from a vertex)
 *		a)every vector represents a vertex, in that vector there a paired entries 
 *		which represents index of the adjacent vertices and the weighted value to them    
 *
 * *****************************************************************************************************/
class Graph
{
private:
	
		
	typedef std::pair<std::pair<int,int>,bool> Pair_PairofInt_Bool;
	std::vector<std::vector<Pair_PairofInt_Bool>> adjList;

    int N,E_undirect,E_direct; //number of nodes N,edges E
	/*mode of the graph - directed or undirected
	*  - directed: every occurence in the vector handled "as one direction"
	*  - undirected: ever occurence in the vector handled as a connection(in both ways)
	*  - 			 if changed from directed mode, only first occurence of a connection relevant
	*/	
    bool directed;
    
	
	void insert_Pair_to_Vector(int index,Pair_PairofInt_Bool p);
	/*recursively search for path and mark as visited */
    /*if during search we found  a already marked one, return true*/
	/*XXXXXXXXXXXXXXXXXXXXcheck itXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXx*/
    bool dsv(int node,int value, std::vector<bool>& visited,std::vector<bool>& finished,std::vector<int>& found,int root);
	

public:
	// construct a vector of vectors to represent an adjacency list
	//one vector represents the to a corresponding node adjacent nodes with an id (integer) and 
	//edge has a value (int)
		

    // Standard Graph Constructor
    Graph(void) 
    {
        N=0;
		E_direct=0;
        E_undirect=0;
		this->directed=true;
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
