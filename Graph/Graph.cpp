#include "Graph.hpp"




// print :
// STATUS: read X
// print  Node  Numbers beginning with 1
void Graph::printTable(void)
{
	
	std::cout << "Display Connection Table" << std::endl;
	std::cout << "Number of nodes:" << N <<std::endl;
	for(unsigned i = 0; i < N; i++)
	{
		std::cout<<(i+1)<<": ";
		for (std::pair<std::pair<int,int>,bool> v : adjList[i])
		{
			if(v.second==true && this->directed)
				std::cout <<" ,(" <<((v.first).first+1) << "|"<< (v.first).second <<")"; 		
			else  if(this->directed==false)
				std::cout <<" ,(" <<((v.first).first+1) << "|"<< (v.first).second <<")"; 		
		}
		std::cout << std::endl;
	}
}




/****************************************************/
// print adjacency list representation of graph
// STATUS: read X
// print  Node  Numbers beginning with 1
void  Graph::printGraph(void)
{
	std::cout << "Display Graph informations:"<< std::endl;

	std::cout << "Number of Nodes: "<<  N << std::endl;
	if(directed)
	{

		std::cout << "Direction Mode:"<< "DIRECTED" <<std::endl;
		std::cout << "Number of Edges: "<<  E_direct << std::endl<< std::endl;
	}else{//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! print real node numbers

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
					std::cout << i+1 << " -->> " << ((v.first).first+1) << " ("<< (v.first).second <<") |X| "; 		
			}
			std::cout << std::endl;
		}
	}else{

		for(unsigned i = 0; i < N; i++)
		{
			for (std::pair<std::pair<int,int>,bool> v : adjList[i])
			{	//maybe duplicated if several same connections !!!!!!!!!!!!!!!!!!!!!!!!!!
				std::cout << i+1 << " --- " << ((v.first).first+1) << " ("<<(v.first).second<<") |X|"; 		
			}

			std::cout << std::endl;
		}
	}


	std::cout << std::endl;
}


/**************************************************/
int Graph::getNodeNumber(void)
// STATUS: read X
{
    #ifdef dbg_graph_getNodeNumber
	std::cout<<"adjList length : "<< adjList.size()<<std::endl;
#endif
return N;
}


/**************************************************/
int Graph::getEdgeNumber(void)
// STATUS: read X

{
int E;
if(directed)
	E=E_direct;
else
	E=E_undirect;

return E;
}

/**************************************************/
int Graph::addNode(void)
// STATUS: read X
{
std::vector<std::pair<std::pair<int,int>,bool>> v;

adjList.push_back(v);
this->N+=1;
return this->N;
}
/****************************************************/
void Graph::insert_Pair_to_Vector(int index,Pair_PairofInt_Bool p)
// STATUS: read x
{
	
	if(adjList[index].size()>0 )
	{	bool inserted_Pair=false;
		//examine connection list of a node for already existing edge
		for (auto it=adjList[index].begin(); it<adjList[index].end(); ++it)
		{
			if(((*it).first).first >= (p.first).first)
			{//insert  new  connection on the right place
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
// STATUS: read X
{
	int E=0;
    if(src<N && dst < N && value>0 && src!=dst )
    {   
	/*
	 * two types of edges:
	 *	directed edge 
	 *	info edge: created in opposite direction of the directed edge
	 *	in case of Mode switch to Undirected Mode, both directions must be available
	 *
	 * */	
		bool first_direct_available=false;
		bool second_direct_available=false;
		bool undirected_exists_counterpart=false;	
		if(directed)
		{   //only consider directed edge,opposite is for info purpose		
			for(std::pair<std::pair<int,int>,bool> p: adjList[src])
			{
			 //in "DIRECTED" mode check if edge is available and if edge is undirected and change it to a directed edge 
				if((p.first).first==dst && (p.first).second==value)
				{	
					if(p.second)
					{//its a directed ede
						first_direct_available=true;//nothsng changed,return same number of edges
					}else
					{//its an info edge,change it to directed
						p.second=true;//make edge directed
						first_direct_available=true;//return same number of edges	
						E_direct++;//already  counted in  E_undirected
					}
				}
			}
			for(std::pair<std::pair<int,int>,bool> p: adjList[dst])
			{
				//check if there  exist already an opposite edge,  otherwise a info have to be created
				//for the purposes of a mode switch
				if((p.first).first==src && (p.first).second==value)
				{	
					//edge is available
					second_direct_available=true;
				}
			}
			if (!first_direct_available)
			{
				std::pair<std::pair<int,int>,bool> p1(std::pair<int,int>(dst,value),true);
				insert_Pair_to_Vector(src,p1);
				E=(++E_direct);
				E_undirect++;
				
			}
			
			if(!second_direct_available)
			{
				std::pair<std::pair<int,int>,bool> p2(std::pair<int,int>(src,value),false);
				insert_Pair_to_Vector(dst,p2);
				E_undirect++;
			}
		}else{
			//check for available edges
			for(std::pair<std::pair<int,int>,bool> p: adjList[src])
			{
				//in UNDIRECTED MODE check if edge already available, may be as directed edge
				//or as info edge
				if((p.first).first==dst && (p.first).second==value)
				{

					first_direct_available=true;
				}
			}
			//check for available edges in the other direction
			for(std::pair<std::pair<int,int>,bool> p: adjList[dst])
			{//it should be checked if undirected or directed mode

				if((p.first).first==src && (p.first).second==value)
				{
					second_direct_available=true;
					
				}
			}
			//add edges if not  already added
			if(first_direct_available==false){
				std::pair<std::pair<int,int>,bool> p1(std::pair<int,int>(dst,value),false);
				insert_Pair_to_Vector(src,p1);	
				E=(++E_undirect);
			}	
			if(second_direct_available==false)
			{
				std::pair<std::pair<int,int>,bool> p2(std::pair<int,int>(src,value),false);
				insert_Pair_to_Vector(dst,p2);
				E=(++E_undirect);
			}	
			}
			
		}
		
        return  E;
    }
    

/**************************************************/

//returns status of Directed Mode
bool Graph::setUndirectedMode(void)
// STATUS: read X
{
	this->directed=false;
	return false;
}


/**************************************************/
bool Graph::getMode(void)
// STATUS: read X
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
	   /*for (std::pair<std::pair<int,int>,bool> p: adjList[node])
	   {
		   if((p.first).first==root && (p.first).second==value)
			   return false;
	   }*/
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

			   if((p.first).second==value && (p.first).first!=root)
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
			   if((p.first).first!=root)//in undirected mode only one edge relevant between two points
			   {
				   if(dsv((p.first).first,0,visited,finished,found,node))
				   {
					   found.push_back(node);
					   return true;
				   }
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
//Debug output: Nodes start fom Node 1:w

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
		
#ifdef dbg_graph_findcircle
		std::cout<<"Start Node "<<(i+1)<<"  ";
#endif
        ret=dsv(i,edge_value, visited, finished,found,i);
        if (ret)
        {   
#ifdef dbg_graph_findcircle
            std::cout <<"Graph::findCircles::found circle with edge_value "<< edge_value <<  
				" from node "<< (i+1) << "::";
            for (std::vector<int>::const_iterator j = found.begin(); j != found.end(); ++j)
                std::cout << *j+1 << ' ';
            std::cout << std::endl;
#else
			
			return true;
#endif
			std::cout << std::endl;	
        }
    }
    
    return ret;
}


		

