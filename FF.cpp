#include "FF.h"
#include "param.h"
#include <iomanip>

void FF::print()
{
      std::cout << std::setw(10) << std::left << Instance_name
              << std::setw(10) << std::right << _Coor.first
              << std::setw(10) << std::right << _Coor.second
              << std::setw(10) << std::right << _QpinDelay
              << std::setw(10) << std::right << _TimingSlack
              << std::setw(10) << std::right << _Power
              << std::endl;
}

void FF::sortNeighbors()
{
    std::sort(_neighbors.begin(), _neighbors.end(),
            [](const NeighborFF& ff1, const NeighborFF& ff2)
            {
                return ff1.second < ff2.second;
            });
}

void FF::setBandWidth()
{
    if (getNeighborSize() > getParam().M) _h = _neighbors[getParam().M].second;
    else _h = _neighbors.back().second;
    
    if (_h > getParam().SqrMaxBandwidth) _h = getParam().MaxBandwidth;
    else _h = std::sqrt(_h);
}

double  FF::doShifting()
{
    double shift_x = 0;
    double shift_y = 0;
    double scale_factor = 0;
    for (int i = 0; i < (int)_neighbors.size();i++)
    {
        FF& n = getParam().get_inst_FF(_neighbors[i].first);
        double h_i = n.getBandwidth();
        double weight = Gaussian(_Coor, n.getOrinCoor(), h_i);
        weight = weight / std::pow(h_i, 4);
        shift_x += n.getOrigX() * weight;
        shift_y += n.getOrigY() * weight;
        scale_factor += weight;
    }
    assert(std::isnormal(scale_factor));
    shift_x = shift_x/scale_factor;
    shift_y = shift_y/scale_factor;
    double ret = std::sqrt(std::pow(shift_x-getX(), 2)+
                           std::pow(shift_y-getY(), 2));
    //std::cout << shift_x << "  "<< shift_y<<std::endl;
    setCoor(shift_x, shift_y);
    return ret; 
}   
