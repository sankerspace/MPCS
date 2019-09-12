#include "Graph.hpp"




// print :
// STATUS: read X
void Graph::printTable(void)
{
	
	std::cout << "Display Connection Table" << std::endl;
	std::cout << "Number of nodes:" << N <<std::endl;
	for(unsigned i = 0; i < N; i++)
	{
		std::cout<<i<<": ";
		for (std::pair<std::pair<int,int>,bool> v : adjList[i])
		{
			if(v.second==true && this->directed)
				std::cout <<" ,(" <<(v.first).first << "|"<< (v.first).second <<")"; 		
			else  if(this->directed==false)
				std::cout <<" ,(" <<(v.first).first << "|"<< (v.first).second <<")"; 		
		}
		std::cout << std::endl;
	}
}

/****************************************************/
// print adjacency list representation of graph
// STATUS: read X
 
void  Graph::printGraph(void)
{
	std::cout << "Display Graph informations:"<< std::endl;

	std::cout << "Number of Nodes: "<<  N << std::endl;
	if(directed)
	{

		std::cout << "Direction Mode:"<< "DIRECTED" <<std::endl;
		std::cout << "Number of Edges: "<<  E_undirect/2 << std::endl<< std::endl;
	}else{

		std::cout << "Direction Mode:"<< "UNDIRECTED" <<std::endl;
		std::cout << "Number of Edges: "<<  E_undirect << std::endl<< std::endl;
	}


	if(directed) 
	{

		for(unsigned i = 0; i < N; i++)
		{
			for (std::pair<std::pair<int,int>,bool> v : adjList[i])
			{
				if(v.second==true)
					std::cout << i << " -->> " << (v.first).first << " ("<< (v.first).second <<") |X| "; 		
			}
			std::cout << std::endl;
		}
	}else{

		for(unsigned i = 0; i < N; i++)
		{
			for (std::pair<std::pair<int,int>,bool> v : adjList[i])
			{	//maybe duplicated if several same connections !!!!!!!!!!!!!!!!!!!!!!!!!!
				std::cout << i << " --- " << (v.first).first << " ("<<(v.first).second<<") |X|"; 		
			}

			std::cout << std::endl;
		}
	}


	std::cout << std::endl;
}


/**************************************************/
int Graph::getNodeNumber(void)

// STATUS: read
{
    #ifdef dbg_graph_getNodeNumber
        std::cout<<"adjList length : "<< adjList.size()<<std::endl;
    #endif
    return N;
}


/**************************************************/
// STATUS: read
int Graph::getEdgeNumber(void)
// STATUS: read
	
{
	int E;
	if(directed)
		E=E_undirect/2;
	else
		E=E_undirect;

	return E;
}

/**************************************************/
int Graph::addNode(void)

// STATUS: read
{
	std::vector<std::pair<std::pair<int,int>,bool>> v;
	
    adjList.push_back(v);
    this->N+=1;
    return this->N;
}
/****************************************************/
void Graph::insert_Pair_to_Vector(int index,Pair_PairofInt_Bool p)
// STATUS: read
{
	
	if(adjList[index].size()>0 )
	{	bool inserted_Pair=false;
		//examine connection list of a node for already existing edge
		for (auto it=adjList[index].begin(); it!=adjList[index].end(); ++it)
		{
			if(((*it).first).first >= (p.first).first)
			{
				adjList[index].insert(it,p);
				inserted_Pair=true;
			}
		}
		if(!inserted_Pair)
			adjList[index].push_back(p);

	}else
	{
		adjList[index].push_back(p);
	}
}




/**************************************************/
//src -> dst always  stored,whenever directed or undirected mode
//ŝrc and dst are index values
int Graph::addEdge(int src,int dst,int value)
// STATUS: read
{
    if(src<N && dst < N && value>0 && src!=dst )
    {   
		bool undirected_exists_counterpart=false;	
		if(directed)
		{   //only consider directed edge,opposite is for info purpose		
			for(std::pair<std::pair<int,int>,bool> p: adjList[src])
			{//it should be checked if undirected or directed mode
			 //in "DIRECTED" mode check if edge is available and if edge is undirected and change it to a directed edge 
				if((p.first).first==dst && (p.first).second==value)
				{	
					if(p.second)
					{//its a directed ede
						return 	E_undirect;//nothing changed,return same number of edges
					}else
					{//its a undirected edge
						p.second=true;//make edge directed
						return E_undirect;//return same number of edges	
					}
				}
			}


			std::pair<std::pair<int,int>,bool> p1(std::pair<int,int>(dst,value),true);
			std::pair<std::pair<int,int>,bool> p2(std::pair<int,int>(src,value),false);
			
			insert_Pair_to_Vector(src,p1);
			insert_Pair_to_Vector(dst,p2);
		}else{
			bool first_direct_available=false;
			bool second_direct_available=false;
			//check for available edges
			for(std::pair<std::pair<int,int>,bool> p: adjList[src])
			{//it should be checked if undirected or directed mode
				//in "UNDIRECTED" mode check if edge is  available and change it to directed otherwise
				//if it is undirected there exists a counterpart which might be directed and should be changed to
				//undirected

				if((p.first).first==dst && (p.first).second==value)
				{

					first_direct_available=true;
				}
			}
			//check for available edges in the other direction
			for(std::pair<std::pair<int,int>,bool> p: adjList[dst])
			{//it should be checked if undirected or directed mode
				//in "UNDIRECTED" mode check if edge is an info edge and change it to directed otherwise
				//undirected

				if((p.first).first==src && (p.first).second==value)
				{
					second_direct_available=true;
					
				}
			}
			//add edges if not  already added
			if(first_direct_available==false){
				std::pair<std::pair<int,int>,bool> p1(std::pair<int,int>(dst,value),false);
				insert_Pair_to_Vector(src,p1);	
			}	
			if(second_direct_available==false)
			{
				std::pair<std::pair<int,int>,bool> p2(std::pair<int,int>(src,value),false);
				insert_Pair_to_Vector(dst,p2);
			}
		}
		
		E_undirect+=2;
        return  E_undirect;
    }
    return -2;//index not valid
    
}

/**************************************************/

//returns status of Directed Mode
//bool Graph::setDirectedMode(void)
// STATUS: read
//{
//	this->directed=true;
//	return true;
//}

//returns status of Directed Mode
bool Graph::setUndirectedMode(void)
// STATUS: read
{
	this->directed=false;
	return false;
}


bool Graph::getMode(void)
// STATUS: read
{
	return this->directed;
}

/**************************************************/
bool Graph::dsv(int node,int value, std::vector<bool>& visited,std::vector<bool>& finished,std::vector<int>& found,int root)
// STATUS: read
{
        
   if (finished[node]==true)
    return false;
   if (visited[node]==true)
   {
	   //if searched path comes back through an info edge(represents undirected connection)
	   //no circle 
	   for (std::pair<std::pair<int,int>,bool> p: adjList[node])
	   {
		   if(p.second==false && (p.first).first==root)
			   return false;
	   }
	   found.push_back(node);
	   return true;//found cycle
   }
   visited[node]=true;
   if(directed)
   {/************* DIRECTED **********************/
	   for (std::pair<std::pair<int,int>,bool> p: adjList[node])
	   {
		 if(value>0)//if edge value important
		 {  //edge value corresponds  and its a valid directed edge
			if((p.first).second==value && p.second==true )
			{
				if(dsv((p.first).first,value,visited,finished,found,node))
				{
					found.push_back(node);
					return true;
				}
			}   
		 }
		 else
		 {//edge value not important
					
			if(p.second==true )
			{		
				if(dsv((p.first).first,0,visited,finished,found,node))
				{
					found.push_back(node);
					return true;
				}
			}
		 
		 }
	   }
   }else
   {
	   /************* UNDIRECTED **********************/
	   for (std::pair<std::pair<int,int>,bool> p: adjList[node])
	   {
		 if(value>0)//if edge value important
		 {  //edge value corresponds  and its a valid directed edge
			if((p.first).second==value)
			{
				if(dsv((p.first).first,value,visited,finished,found,node))
				{
					found.push_back(node);
					return true;
				}
			}   
		 }
		 else
		 {
					
			 if(dsv((p.first).first,0,visited,finished,found,node))
			 {
				 found.push_back(node);
				 return true;
			 }
		 
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
// STATUS: read
{
    //check for every node
    
    
    bool ret=false;
    for (unsigned i = 0; i < N; i++)
    {
        std::vector<int> found;
        std::vector<bool> visited(N,false);
        std::vector<bool> finished(N,false);
        ret=dsv(i,edge_value, visited, finished,found,i);
        if (ret)
        {   
#ifdef dbg_graph_findcircle
            std::cout << "Graph::findCircles::found circle with edge_value "<< edge_value <<  
				"from node "<< i << "::";
            for (std::vector<int>::const_iterator j = found.begin(); j != found.end(); ++j)
                std::cout << *j << ' ';
            std::cout << std::endl;
#else
			return true;
#endif
            ret=true;
        }
    }
    
    return ret;
}


		

