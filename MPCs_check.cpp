#include "MPCs_check.hpp"


/*********************************************************************
*
**********************************************************************/

bool check_communication_Schedule(comm_schedule_type& comm)
{
    bool ret=false;
    const std::size_t size=comm.size();
    unsigned current_lm=1,old_lm=0;
    unsigned int lm_comm[size]={0};//track logical moment for every  communication
    unsigned limit=0;
    while(current_lm  !=  old_lm)
    {   old_lm=current_lm;
        for (int j=0;j<size;j++)
        {
            FromIdToId_Pair_type        id_global=comm[j].first;
            FromIndexToIndex_Pair_type  indices_global=comm[j].second;
            if(indices_global.first==limit)
            { 
                 //check if both index  are the same In current limit
                 //a immediate communication is possible and "lm" can be set
                 if(indices_global.second==limit)
                 {
                    
                 }
            
            }else if(indices_global.second==limit)
            {
                 
            
            
            }
           
           
           
           
           
           
            
        }
    }
    
    
    return ret;
}
