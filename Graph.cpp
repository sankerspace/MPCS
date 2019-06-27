#include "Graph.hpp"



//using namespace std;



// print adjacency list representation of graph
void  Graph::printGraph(void)
{
    std::cout << "Display Graph informations:"<< std::endl;
    std::cout << "Number of Nodes: "<<  N << std::endl;
    std::cout << "Number of Edges: "<<  E << std::endl<< std::endl;
    
	for (unsigned i = 0; i < N; i++)
	{
		// print current vertex number
		//std::cout << i << " --> ";

		// print all neighboring vertices of vertex i
		for (std::pair<int,int> v : adjList[i])
			std::cout << i << " --> " << v.first << " ("<<v.second<<")"<<std::endl;
		std::cout << std::endl;
	}
}

/**************************************************/
int Graph::getNodeNumber(void)
{
    #ifdef dbg_graph_getNodeNumber
        std::cout<<"adjList length : "<< adjList.size()<<std::endl;
    #endif
    return N;
}


/**************************************************/
int Graph::getEdgeNumber(void)
{
    //int n=0;
    //for (unsigned i = 0; i < N; i++)
	//{
	//	n+=adjList[i].size();
	//}
	
	return E;
}

/**************************************************/
int Graph::addNode(void)
{
    std::vector<std::pair<int,int>> v;
    adjList.push_back(v);
    this->N+=1;
    return this->N;
} 

//for src and dst no index values
int Graph::addEdge(int src,int dst,int value)
{
    if(src<N && dst < N && value>0)
    {       
        for(std::pair<int,int> p: adjList[src])
        {
           if(p.first==dst)
            return -1;
        }
        std::pair<int,int> p(dst,value);
        adjList[src].push_back(p);
        E++;
        return  E;
    }
    return -2;
    
}



bool Graph::dsv(int node,int value, std::vector<bool>& visited,std::vector<bool>& finished,std::vector<int>& found)
{
        
   if (finished[node]==true)
    return false;
   if (visited[node]==true)
   {
    found.push_back(node);
    return true;//found cycle
   }
   visited[node]=true;
   for (std::pair<int,int> p: adjList[node])
   {
     if(value>0)
     {
        if(p.second==value)
        {
            if(dsv(p.first,value,visited,finished,found))
            {
                found.push_back(node);
                return true;
            }
        }   
     }
     else
     {
        if(dsv(p.first,0,visited,finished,found))
        {
            found.push_back(node);
            return true;
        }
     
     }
   }
   finished[node]=true; 
   return false; 
}



/*
*https://de.wikipedia.org/wiki/Zyklus_(Graphentheorie)
*Für jeden Knoten v: visited(v) = false, finished(v) = false
Für jeden Knoten v:
  DFS(v)
  
DFS(v):
  if finished(v)
    return
  if visited(v)
    "Zyklus gefunden" und Abbruch
  visited(v) = true
  für jeden Nachfolger w
    DFS(w)
  finished(v) = true  
*/

bool Graph::findCircles(int edge_value)
{
    //check for every node
    
    
    bool ret=false;
    for (unsigned i = 0; i < N; i++)
    {
        std::vector<int> found;
        std::vector<bool> visited(N,false);
        std::vector<bool> finished(N,false);
        ret=dsv(i,edge_value, visited, finished,found);
        if (ret)
        {   
            #ifdef dbg_graph_findcircle
            std::cout << "Graph::findCircles::found circle  with edge_value "<< edge_value <<"::";
            for (std::vector<int>::const_iterator j = found.begin(); j != found.end(); ++j)
                std::cout << *j << ' ';
            std::cout << std::endl;
            #endif
            return true;
        }
    }
    
    return false;
}


		

