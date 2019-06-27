

#include "MPC_Generator.hpp"
#include <boost/filesystem/fstream.hpp>
#include <memory>
/*
int reset_choosenList(int* list,int size,int from)
{
    
    if (from >=size)
        return -1;   
    for(int i=0;i<size;i++)
    {
        if(i>=from)
        {
            
        }
    }
    
    return 0;
}*/

template<typename T>
std::unique_ptr<T*[]> generate2D_CharArray(size_t s1,size_t s2)
{
   std::unique_ptr<T*[]> ptr_2Dim (new T*[s1]); 
   for(size_t i=0;i<s1;i++){
        std::unique_ptr<T[]> ptr(new T[s2]);
        for(size_t j=0;j<s2;j++)
        {
            ptr[j]=0;
        }
        ptr_2Dim[i]=&ptr[0];
    }
    return ptr_2Dim;
}


unsigned int  power_Base2(unsigned int  n)
{
    unsigned int  v=1,i;
    for(i=0;i<n;i++)
    {
        v *=2;
    }
    return v;
}

unsigned int factorial(unsigned int n) 
{ 
    unsigned int res = 1, i; 
    for (i = 2; i <= n; i++) 
        res *= i; 
    return res; 
} 

/*
 a=power_Base2(number-1);
    b=number-1;
*/
void prepare_Directions(const size_t a,const size_t b,std::unique_ptr<char*[]>& directions)
{
    int u=2;
    int s=0;
    std::unique_ptr<int[]> control_init(new int[b]);
    std::unique_ptr<int[]> control_current(new int[b]);
    for(size_t z=0;z<b;z++)
    {   
        control_init[z]=u;
        control_current[z]=u;
        u *= 2;
    }
    for(size_t j=0;j<b;j++)
    {
        for(size_t i=0;i<a;i++)
        {   
            if((control_current[j]  % 2)==0)
            {  
                //directions[i*b + j] = '+';
                directions[i][j] = '+';
                std::cout<< '+';
            }else{
                //directions[i*b + j] = '-'; 
                directions[i][j] = '-';
                std::cout<< '-';
            }
            
            s=((i+1) %  (control_init[b-1]/ control_init[j]) );
            if(s==0)        
            {
                control_current[j]--;
            }
            
        }
        std::cout <<  std::endl;
    }

}



int generate_MPC(std::string filename,int number)
{
    BF::path p(filename.c_str());
    BF::ofstream ofs{p};
    //ofs << "Number of Nodes:"<<number<<"\n";
    
    //std::string output[number];
    //int control_choosen[number]={0};
   
    //int index_choosen=0;
    
    //std::unique_ptr<int[]> control_adjazentMatrix(new  int[number]);//position through the columns
     std::unique_ptr<int*[]> adjMatr = generate2D_CharArray<int>(number,number);
    
    //size_t s0  = number;
    //size_t s1 = factorial(number-1);
    //size_t s2 = (number-1);
    //char str_gen[s0][s1][s2]={0};
    
    for (size_t i=0;i<(size_t)number;i++)
    {
       // control_choosen[i]=s2;
        adjMatr[i][i]=0;
    }
    
    
    const size_t s3=power_Base2(number-1);
    const size_t s4=number-1;
    //char directions[s3][s4]={0};
   // char** directions = new char*[s3];
    std::unique_ptr<char*[]> directions = generate2D_CharArray<char>(s3,s4);
   // prepare_Directions(s3,s4,(char*)directions);
     prepare_Directions(s3,s4,directions);
    /*
    while(true)
    {
        if(control_choosen[0]>=0)
        {
          if(index_choosen==number)
          { 
            index_choosen=0;
          }
         
          //interate through the adjacence matrix 
          //through iterating a new CommList is generated
         for(int i=0;i<number;i++)
         {
           for(int j=0;j<number;j++)
           {
                
            
           } 
         }
        
        }else{
            break;
        }
        
        
    }
    */
    
   
    return 0;
}
