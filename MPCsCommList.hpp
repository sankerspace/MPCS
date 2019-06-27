#ifndef _MPCSCOMMLIST_HEADER_
#define _MPCSCOMMLIST_HEADER_


//#include "MPCs.hpp"
#include "ReadList.hpp"
#include <vector>
#include <iostream>

using FromIdToId_Pair_type        =  std::pair<int,int>;
using FromIndexToIndex_Pair_type =  std::pair<int,int>;
using comm_schedule_type           =  std::vector<std::pair<FromIdToId_Pair_type,FromIndexToIndex_Pair_type>>; //one schedule from a set of nodes
using comm_schedules_type          =    std::vector<std::vector<std::pair<FromIdToId_Pair_type,FromIndexToIndex_Pair_type>>>;//several schedules 




/*
* Creates a sorted Communication Ordering from given Node Schedules
* The created vector is a more specific map about communications between nodes
* comm_vector_type: 
*   [(ID_sendingNode,Id_ReceivingNode),(Index_sendingNode,Index_ReceivingNode)]  
*/
comm_schedule_type  get_communication_Schedule(nodes_cycle_type& nodes_schedules,int& error);
void                sort_communication_Schedule(comm_schedule_type& comm);
void                printComm(comm_schedule_type& comm);

bool                check_communication_Schedule(comm_schedule_type& comm);



#endif
