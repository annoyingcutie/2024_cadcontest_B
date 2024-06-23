#include "MS.h"

#include "param.h"
MS::MS()
{
    _iterCnt.resize(getParam().getFFSize());
    for (int i = 0; i < (int)_iterCnt.size(); i++)
    {
        _iterCnt[i].second = i;
    }
}
void MS::run()
{
   
    buildRtree();
    std::cout<<"Finish Rtree..."<<std::endl;
    initKNNs();
     std::cout<<"Finish initKNN.."<<std::endl;
    shiftFFs();
     std::cout<<"Finish shiftFF..."<<std::endl;
}
void MS::buildRtree()
{
    auto& m = getParam();
    std::vector<PointWithID> points;
    
    points.reserve(m.getFFSize());
    for (int id = 0; id < m.getFFSize(); id++)
    {
        FF& f = m.get_inst_FF(id);
        points.emplace_back(std::make_pair(Point(f.getX(),f.getY()), id));
    }
    _rtree.insert(points.begin(), points.end());

}
void MS::initKNNs()
{
    auto& m = getParam();
    #pragma omp parallel for num_threads(getParam().ThreadNum)
    for (int id = 0; id < m.getFFSize(); id++)
    {
        FF& f = m.get_inst_FF(id);
        getKNN(id);
        if (f.getNeighborSize()==1)
        {
            f.setShifting(false);
        }
        else 
        {
            f.setBandWidth();
        }
    }

}

void MS::getKNN(int id)
{

    auto& m = getParam();
    FF& f = m.get_inst_FF(id);
    std::vector<PointWithID> neighbors;
    neighbors.reserve(getParam().K);
    _rtree.query(bgi::nearest(Point(f.getOrigX(), f.getOrigY()), getParam().K), 
                              std::back_inserter(neighbors));
    BOOST_FOREACH(PointWithID const&p, neighbors)   
    {
        double dis = SE_Distance(m.get_inst_FF(id).getOrinCoor(),
                                             m.get_inst_FF(p.second).getOrinCoor());
        if (dis < getParam().SqrMaxDisp) f.addNeighbor(p.second, dis);
    }
    f.sortNeighbors();
}
void MS::shiftFFs()
{
    auto& m = getParam();
    #pragma omp parallel for num_threads(getParam().ThreadNum)
    for (int i = 0; i < m.getFFSize(); i++)
    {
        FF& nowFF = m.get_inst_FF(i);
        if (!nowFF.isShifting()) 
        {
            _iterCnt[nowFF.get_FF_id()].first = 0;
            continue;
        }
        int iter = 0;
        while (++iter)
        {
            double dis = nowFF.doShifting();
            if (dis <= getParam().Tol)
            {
                nowFF.setShifting (false);
                _iterCnt[nowFF.get_FF_id()].first = iter;
                break;
            }
        }
    }
    std::sort (_iterCnt.begin(), _iterCnt.end(), 
               std::less<std::pair<int, int> >());
}

