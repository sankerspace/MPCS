#include "MPCs.hpp"


std::string _convertIntArraytoString(int* arr,int size)
{
    std::ostringstream oss;
    oss << '{';
    for(int i=0;i < size;i++)
    {
        oss << arr[i] << ',';     
    }
    oss << '}';
    std::string s = oss.str();
    return s;
}
