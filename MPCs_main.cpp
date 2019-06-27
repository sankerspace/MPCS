


#include "MPCsCommList.hpp"
#include "MPCs_check.hpp"
#include <iostream>
#include <fstream>

using  namespace std;



int main(int argc,char** argv) {
	string f = string("Example.MPCs.txt");
	int error=0;
	list_type  list=ReadMPCsLists(f,error);
	//printLists(list);
	std::cout  << '\n' <<"[ReadMPCsLists()]error code:"<< error << std::endl;
  	if(error)
  	{
  	    int i=1;
  	    for (auto it = list.cbegin(); it != list.cend(); ++it)
        {
        
        nodes_cycle_type schedules=*it;
        comm_schedule_type comm = get_communication_Schedule(schedules,error);
        printComm(comm);
  	    std::cout  << '\n' <<'['<<"List-" << i++ << ']' <<"[get_communication_Schedule()]error code:"<< error << std::endl;
        
        std::cout  << '\n' <<'['<<"List-" << i++ << ']' <<"[get_communication_Schedule()]Perform sort according indizes:"<< std::endl;
        sort_communication_Schedule(comm);
        printComm(comm);
        }
  	    
  	}
  	
  	
  	return 0;
}
