Graph(TestGraph):
-----------------
A class which handles creation of nodes and edges of a graph "on-the-fly",
that means that after initiating a class there are no nodes and edges 
at the beginning. Every edge must have a value(or weight).

function dsv() searches for a "circle" from a node with edges on that circle 
restricted to the same weight(or not = 0).

MPC (Multipartner Communication)
---------------------------------
Intro: N nodes need to communicate with each other, therefore N nodes 
	have to arrange a communication cycle to exchange informations.
	For every cycle N nodes have to communicate 
	according to their Commlists(Every node has its own).
        (According to a CommList from node f, 
	 not all communications to the remaining N-1 nodes have to be defined,
	 but at least one node)
	
	Every node i from N nodes have its communication List CommList.
	Such a CommList is a description in which order the i-th node 
        communicates to zhe N-1 other nodes.CommList[i] is the i-th CommList 
 	from the i-th node.
	 Example(N=3 nodes): CommList[0] = ((2,+),(3,-))
	 Node 1 sends data to Node 2 and then receive data to Node 3.

ReadList:
	A text file contains Y possible communication cycles(MPC instances).
	At every MPC instances,there is a description of the communication 
	between X nodes.

	ReadList reads the CommLists from x Nodes(in a MPC-Instance) from a 
	text file encoded in a defined way. 
	x CommLists from x nodes,describes one communication cycle.
	A communication cycle forms one MPC instance.  
	
	Datatypes used:
	 nodes_schedule_type := A CommList from one Node inside a MPC-instance
	 nodes_cycle_type    := One MPC-Instance(constructed by X Comm-Lists)
	 list_type	     := a list of Y MPC-Instances
	Short Summary:
	 ReadList reads all MPC-instances from a text-file and store them 
	 in a list_type.

	Example of such a text file:

	(2,+),(3,-),(3,+)
	(1,-),(4,+)
	(1,+),(4,+),(4,-),(1,-)
	(3,-),(2,-),(3,+);

MPCsCommList:
	MPCsCommList creates an improved representation "Improved_CommList" 
	for further analysis of a MPC-Instance.
	
	get_communication_Schedule():
		From a MPC-Instance convert all CommLists from the X nodes to 
		 following representation "Improved_CommList":
		(Node-A,Node-B,i-th,j-th)::
			At the i-th position in the Comm-List of Node-A, 
			Node-A sends data to Node-B, therefore at 
			the j-th position of the CommList from Node-B,
			Node-B is receiving data from Node-A.
		If some correlations between Node-A and Node-B are notcorrect, 
		variable "error" is set to a value.

	printComm(): prints such a representation Improved_CommList

	sort_communication_Schedule():
		performs a sort on Improved_CommList according 
		to i-th value and then according to the j-th value.

MPCs_check:
	We take such an Improved_CommList and create a directed graph 
	according to Improved_CommList.if a node Node-A sends data to a 
	node Node-B, then we have a directed edge from Node-A to Bode-B.#

	Further an analysis on an Improved_CommList is performed in order 
	to derive the "logical moment"  of every communication.
	(According to the values i and j of every Communication)
	The logical moment of a communication between a Node-A to 
	Node-B is is marked by a value/weight on the edge from Node-A to Node-B.
 	The Logical Moment is a value which indicates the ordering 
  	of the communication according to the constellation of a MPC-Instance.
	(constellation of a MPC-Instance decribes a communication possible at 
	  a specific moment if we overview all CommList at the same time.)

	We get a graph with nodes and edges and every edge is marked by 
	a value,we translate that "directed graph" to an "undirected graph"
	and search for one cycle in that graph with every edge 
	containing the same weight/value in that cycle. 

	if we found such a cycle in a  graph, 
	we get indication for a possible "Deadlock".

	Short Summary:
	 MPCs_check checks for a possible Deadlock 
	 in a MPC-instance(at least one has to be found,noting else).
	
	MPCs_check example:
				        _____
		 ---------------| 1 |<------------
		|		          |   		      | 1
		| 0	              |		          | 
		|		          | 5	          |
	  __v___              |             __|__
	  | 2 |		          ------------->| 3 | 
  	  |___|		          ------------->|___| 
		|		          |     4         |
		|		          |               |
		|3		          |               |
		|		          |               | 2
		 ------------->	| 4 |<--------------   

				
SUB PROJECTS
------------------	
					
Graph:(Version 1.0 - Build 1)
	Implementation  of a custom Graph solution, which combines directed and undirected Graphs
	under one class.More information under Graph.hpp
	This represents a custom solution.
BoostGraph:(Plan Phase -  not Implemented)
	Implementation of custom Graph solution with use of the Boost Graph Library.
Generator:


