

#include "MPCsCommList.hpp"
#include <array>



/*********************************************************************
*
**********************************************************************/

comm_schedule_type get_communication_Schedule(nodes_cycle_type& nodes_schedules,int& error)
{
size_t list_size=nodes_schedules.size();
comm_schedule_type comm;
error=1;
for (int i=list_size-1;i>=0;i--)
    {
        //counts every interacting occurence of node P_x to another node P_y
        int first_counter[list_size]={0};
        //counts every occurence from every another node P_y interacting with node P_x
        int last_counter[list_size]={0};
        int schedule_size_from=nodes_schedules[i].size();
        nodes_schedule_type FromNode_node_schedule=nodes_schedules[i];
        for(int j=0;j<schedule_size_from;j++)
        {   
           
            int from_from_id_index=i;
            int from_to_id_index=FromNode_node_schedule[j].first-1;  //z-1          
            char from_to_polarity=FromNode_node_schedule[j].second;

            
            if(from_to_id_index <  from_from_id_index) //no double counting for first_counter and last_counter
            {   
                //don't  increment  until  if(...) checked,otherwise last_counter  
                //would be 
                first_counter[from_to_id_index]++;//increment occurence to opposite  node
                int schedule_size_to=nodes_schedules[from_to_id_index].size();
            
                nodes_schedule_type ToNode_node_schedule=nodes_schedules[from_to_id_index];
                int to_to_id_index=from_to_id_index;
                //Number of already observed schedules at opponent  node (from_to_id_index) aiming
                //on current node (from_from_id_index)
                int tmp=last_counter[to_to_id_index];
                
                for(int l=0;l < schedule_size_to;l++)
                {
                    int to_from_id_index=ToNode_node_schedule[l].first-1;            
                    char to_from_polarity=ToNode_node_schedule[l].second;
                    if(from_from_id_index==to_from_id_index)
                    {
                        
                        if(tmp > 0){
                            tmp--;
                        }else
                        {
                            last_counter[to_to_id_index]++;
                            FromIdToId_Pair_type       pair_1;
                            FromIndexToIndex_Pair_type pair_2;
                            std::pair<FromIdToId_Pair_type,FromIndexToIndex_Pair_type> pair_3;
                            
                            if(from_to_polarity=='+' && to_from_polarity=='-')
                            {
                                pair_1.first=from_from_id_index+1;//we want id therefore +1
                                pair_1.second=from_to_id_index+1;
                                pair_2.first=j;//index at from_from_id_index-th schedule
                                pair_2.second=l;//index at from_to_id_index-th schedule
                                pair_3.first=pair_1;
                                pair_3.second=pair_2;
                                comm.push_back(pair_3);
#ifdef  dbg
                                std::cout<<"[get_communication_Schedule()]::pairAdded::"
                                    <<'(' << pair_1.first  << ','
                                          << pair_1.second << ';'
                                          << pair_2.first  << ',' 
                                          << pair_2.second  <<')';
                                std::cout<<"::"
                                << "i="<< i << ','
                                << "j="<< j << ','
                                << "l="<< l << ','
                                << "first_counter="<< _convertIntArraytoString(first_counter,list_size)<<',' 
                                << "last_counter="<< _convertIntArraytoString(last_counter,list_size) 
                                <<  std::endl;
                                
                                
                                
#endif                                         
                                //last_counter[from_from_id_index]++;
                                break; //node found break current for loop
                            }else if(from_to_polarity=='-' && to_from_polarity=='+')
                            {  
                                pair_1.first=to_to_id_index+1;//we want id therefore +1
                                pair_1.second=to_from_id_index+1;
                                pair_2.first=l;
                                pair_2.second=j;
                                pair_3.first=pair_1;
                                pair_3.second=pair_2;
                                comm.push_back(pair_3);
#ifdef  dbg
                                
                                std::cout<<"[get_communication_Schedule()]::pairAdded::"
                                    <<'(' << pair_1.first  << ','
                                          << pair_1.second << ';'
                                          << pair_2.first  << ',' 
                                          << pair_2.second  <<')';
                               std::cout<<"::"
                                << "i="<< i << ','
                                << "j="<< j << ','
                                << "l="<< l << ','
                                << "first_counter="<< _convertIntArraytoString(first_counter,list_size)<<',' 
                                << "last_counter="<< _convertIntArraytoString(last_counter,list_size) 
                                <<  std::endl;

#endif                                                         
                               // last_counter[from_from_id_index]++;
                                break; //node found break current for loop
                            }else
                            {
                                error=-1;
                                break;
                            }
                        }
                    }
                }//l-loop
            }
        } // j -loop 
        int sum_first=0,sum_last=0;
        for(int k=0;k < list_size-1;k++)
        {
            sum_first+=first_counter[k];
            sum_last+=last_counter[k];
        }     
        if (sum_first !=  sum_last)
        {
            error=-2;
            
        }
        
        
        
         
    }//i - loop
    
return comm;
}


/*********************************************************************
*
**********************************************************************/

void printComm(comm_schedule_type& comm)
{
     std::cout << "(ID_from,ID_to;Index_from,Index_to)" <<  std::endl;
      std::cout << "----------------------------------" <<  std::endl;
     for (auto it = comm.cbegin(); it != comm.cend(); ++it)
     {
        FromIdToId_Pair_type pair_1=it->first;
        FromIndexToIndex_Pair_type pair_2=it->second;
        std::cout << '('<<pair_1.first<<","<<pair_1.second<<";"<<pair_2.first  << "," << pair_2.second<<')'<< std::endl;
     }
}


/*********************************************************************
*

**********************************************************************/

void sort_communication_Schedule(comm_schedule_type& comm)
{   
    //FromIdToId_Pair_type         pair_1;
    FromIndexToIndex_Pair_type   pair_x,pair_y,pair_a,pair_b;
    bool change=true;
    comm_schedule_type::size_type sz=comm.size();
    while(change)
    {   
        change=false;
        for(unsigned i=0;i<(sz-1);i++)
        {   
            pair_a=comm[i].first;
            pair_b=comm[i+1].first;
            pair_x=comm[i].second;
            pair_y=comm[i+1].second;
            if (pair_x.first >  pair_y.first)
            {
                comm[i].first=pair_b;
                comm[i+1].first=pair_a;
                comm[i].second = pair_y;
                comm[i+1].second=pair_x;
                change=true;
            }else if (pair_x.first == pair_y.first)
            {
                if (pair_x.second > pair_y.second)
                {
                    comm[i].first=pair_b;
                    comm[i+1].first=pair_a;
                    comm[i].second = pair_y;
                    comm[i+1].second=pair_x;
                    change=true;
                }
            }

        }
    }
}









