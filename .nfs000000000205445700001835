#ifndef _MS_H_
#define _MS_H_

#include "def.h"
class MS{
    
public:
    MS();
    void run();
    std::vector<std::pair<int, int> >& getIterCnt() {return _iterCnt;} //count,FFID
 //public for unit test
    void buildRtree  ();
    void initKNNs    ();
    void shiftFFs    ();
    void getKNN      (int id);
private:
    bgi::rtree<PointWithID, bgi::quadratic<P_PER_NODE> > _rtree;
    std::vector<std::pair<int, int> > _iterCnt;

};

#endif