#ifndef FFBANKING_H
#define FFBANKING_H

#include "def.h"
#include "FF.h"


#include <cstring>
#include <algorithm>
#include <climits>





class FFBanking {
public:

    FFBanking();
    void buildTree();
    void selectFF();
    void buildTable();
    void banking();
    void run();
    void printUseList();
    


private:
    bgi::rtree<BoxWithID, bgi::quadratic<P_PER_NODE> > B;
    std::vector<BoxWithID> flipflops;
    std::vector<FF> useList;
    std::vector<FF> TBmerge;
    std::vector<  std::vector< std::unordered_map<int, int> >  > FF_count;
    //std::vector<std::vector<int>> dp(useList.size() + 1, std::vector<int>(bitsLCM + 1, INT_MAX));
    std::vector<std::vector<int>> dp;
    int bitsLCM ;


    double calPACost(FF ff);
    
};

/*
long long gcd(long long int a, long long int b) 
{ 
  if (b == 0) 
    return a; 
  return gcd(b, a % b); 
} 
  
// Function to return LCM of two numbers  
long long lcm(int a, int b) 
{ 
    return (a / gcd(a, b)) * b; 
}
*/

#endif
