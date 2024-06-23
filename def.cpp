#include "def.h"

double SE_Distance(const L_Coor& p1, const L_Coor& p2)//SquareEuclidean
{
        return std::pow(p1.first  - p2.first , 2) + std::pow(p1.second - p2.second, 2);
}

double MH_Distance(const L_Coor& p1, const L_Coor& p2)//Manhattan
{
        return std::abs(p1.first  - p2.first) + std::abs(p1.second - p2.second);
}

double Gaussian(const L_Coor& p1, const L_Coor& p2,const double bandwidth)
{
    double nom = SE_Distance(p1, p2);
    double denom = -2 * std::pow(bandwidth, 2);
    double ans = std::exp(nom/denom);
    return ans;

}

double SE_Distance_ID(const L_Coor& p1, const PointWithID& p2)
{
    return std::pow(p1.first  - bg::get<0>(p2.first), 2) + std::pow(p1.second - bg::get<1>(p2.first), 2); 
}

double MH_Distance_ID(const L_Coor& p1, const PointWithID& p2)
{
    return std::abs(p1.first  - bg::get<0>(p2.first)) + std::abs(p1.second - bg::get<1>(p2.first));
}