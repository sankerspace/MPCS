#ifndef __MPC_GENERATOR__
#define  __MPC_GENERATOR__

#define BOOST_FILESYSTEM_NO_DEPRECATED

#include <iostream>
#include <boost/filesystem.hpp>
#include <string>
namespace BF = boost::filesystem; 	

int generate_MPC(std::string filename,int number);




#endif

