#include  "ReadList.hpp"
#include <iostream>               // for std::cout
#include <fstream>
#include <memory>
#include <sstream>

list_type ReadMPCsLists(std::string& filename,int& error){

/*
vector:	vector 1: pair(1,+),pair(2,-),pair(3,+)....   
		vector 2: pair(1,+),pair(2,-),pair(3,+).... 
		vector 3: pair(1,+),pair(2,-),pair(3,+).... 
		.
		.
		.

*/
list_type lists;

std::string line;
std::ifstream myfile(filename.c_str());
error=1;//init with positive execution 
std::unique_ptr<nodes_cycle_type> node_list (new nodes_cycle_type);
std::unique_ptr<nodes_schedule_type> comm_list;
std::pair<int,char> p;

if (myfile.is_open())
  {
    int list_end=1;
    int check_pair=0;
#ifdef dbg 
    int line_count=0;
    int char_count=0;
#endif
	while ( getline (myfile,line) )
	{   
#ifdef dbg 
        line_count++;
        char_count=0;
#endif
	    bool newComm=false;
	    char c;
	    std::unique_ptr<std::vector<char>> digital (new std::vector<char>);
	    if(error < 0) 
	        break;
      	for ( std::string::iterator it=line.begin(); it!=line.end(); ++it)
		{
		    c=*it;
		    
		    if(list_end == 0 && error>0)        //current list
		    {
		      if(c==';')
		      { //reached the end of all communication cycles
		        list_end++;
		        check_pair=0;
		        node_list->push_back(*comm_list);//add to global list########
		        lists.push_back(*node_list);//a new LIST ####################
		        node_list.reset(new std::vector<std::vector<std::pair<int,char>>>);  
		      }else if(c=='(' && check_pair==0)
		      {
		        if (!newComm) 
		        {   //is it a new schedule
		            newComm=true;
		            node_list->push_back(*comm_list);//add to global list########
		            comm_list.reset(new std::vector<std::pair<int,char>>);
		        }
		        check_pair=1;
		      }else if(c==')'&& check_pair==2)
		      {
		        check_pair=0;
		        comm_list->push_back(p);//a new pair######################### 
		      }else if(check_pair==1 && c==',')
		      {
		        //all digits consumed in a pair
		        std::istringstream iss(std::string(digital->begin(),digital->end()));		        
		        iss >> p.first;
		        		        
		        if (iss.fail() && iss.bad()){
		            error=-4;
		            std::cout << "ERROR::[ReadList]::Error in List,no Digits."<<std::endl;
		            std::cout << "ERROR::[ReadList]::line::["<< line << "]" << std::endl;
#ifdef dbg 
                std::cout << "ERROR::[ReadList]::"<< filename <<"::"<< line_count << "" << std::endl;
                
                std::stringstream ss;
                if (char_count!=0){
                    ss << "ERROR::[ReadList]::" << line.substr(0,char_count-1) << " >" <<line.at(char_count)<< "< " << line.substr(char_count+1) << std::endl;
                    std::cout << ss.str()  << std::endl;
                }
               
#endif
		        }
		        check_pair=2;
		        digital.reset(new std::vector<char>);
		      }else if(check_pair == 1)
		      {
		        digital->push_back(c); //combine several digits
		        
		      }else if(check_pair == 2 && (c=='+' || c=='-'))
		      {
		        
		        if(c=='+'){
		            p.second='+';
		        }else if(c=='-')
		        {
		            p.second='-';
		        }
		      }else if(c!=',' && check_pair != 0)
		      {
		        error=-2;
		        std::cout << "ERROR::[ReadList]::Error in List,false Characters."<<std::endl;
		        std::cout << "ERROR::[ReadList]::line::["<< line << "]" << std::endl;
#ifdef dbg 
                std::cout << "ERROR::[ReadList]::"<< filename <<"::"<< line_count << "" << std::endl;
                
                std::stringstream ss;
                if (char_count!=0){
                    ss << "ERROR::[ReadList]::" << line.substr(0,char_count-1) << " >" <<line.at(char_count)<< "< " << line.substr(char_count+1) << std::endl;
                    std::cout << ss.str()  << std::endl;
                }
               
#endif
		      }
		    }else if(list_end > 0 && error>0){                  //end of list (or start of a new list)
		       if(c=='(' && check_pair==0)
		       {//a new list begins
		        list_end=0;
		        check_pair=1;
		        newComm=true;
		        comm_list.reset(new std::vector<std::pair<int,char>>);
		       } 
		    }else{
		        error=-3;
		        std::cout << "ERROR::[ReadList]::Error in List,false Characters."<<std::endl;
		        std::cout << "ERROR::[ReadList]::line::["<< line << "]" << std::endl;
#ifdef log 
                std::cout << "ERROR::[ReadList]::"<< filename <<"::"<< line_count << "" << std::endl;
                
                std::stringstream ss;
                if (char_count!=0){
                    ss << "ERROR::[ReadList]::" << line.substr(0,char_count-1) << " >" <<line.at(char_count)<< "< " << line.substr(char_count+1) << std::endl;
                    std::cout << ss.str()  << std::endl;
                }
               
#endif
		        break;
		    }
    		if(error < 0) 
	        break;
	        char_count++;
    	}
        
    }
    myfile.close();
  }
  else{
  	std::cout << "ERROR::[ReadList]::Unable to open file."<<std::endl;
  	error=-1;
  	}; 


return lists;
}



void printLists(std::vector<std::vector<std::vector<std::pair<int,char>>>> lists){
    
    for(std::vector<std::vector<std::vector<std::pair<int,char>>>>::iterator it = lists.begin(); it != lists.end(); it++) { // iterate through all lists
        for(std::vector<std::vector<std::pair<int,char>>>::iterator iter = it->begin(); iter != it->end(); iter++) {          //iterate through one list (all communication schedules)
            for(std::vector<std::pair<int,char>>::iterator iterate = iter->begin(); iterate != iter->end(); iterate++) {         //iterate through One communication schedule
                if ((iterate+1)!=iter->end()){
                    std::cout  << '('<< iterate->first << ',' << iterate->second << ')' << ','; 
                }else{
                    std::cout  << '('<< iterate->first << ',' << iterate->second << ')'; 
                }
            }
            if((iter+1) != it->end())
            {
                std::cout << std::endl; 
            }else{
                std::cout << ';' << std::endl; 
            
            }
        }
       std::cout << std::endl;   
    }

}


































