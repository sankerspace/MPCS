#ifndef _READLIST_HEADER_
#define _READLIST_HEADER_


#include "MPCs.hpp"
#include <list>
#include <vector>
#include <utility>
#include <string>
#include <iostream>

/*
* list_type : several different compilation of schedules representing communications
* nodes_cycle_type: One specific cycle,
* nodes_schedule_type
*/
using list_type             =    std::vector<std::vector<std::vector<std::pair<int,char>>>>;
using nodes_cycle_type      =    std::vector<std::vector<std::pair<int,char>>>;
using nodes_schedule_type   =    std::vector<std::pair<int,char>>;

list_type  ReadMPCsLists(std::string& filename,int& error);

void printLists(list_type lists);








#endif
