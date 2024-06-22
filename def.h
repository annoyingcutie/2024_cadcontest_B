#ifndef _DEF_H_
#define _DEF_H_


#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <string>
#include <map>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <cassert>

#pragma GCC system_header
#include <boost/geometry.hpp>
#include <boost/geometry/geometries/point.hpp>
#include <boost/geometry/index/rtree.hpp>
#include <boost/foreach.hpp>
#define P_PER_NODE 16

namespace bg = boost::geometry;
namespace bgi = boost::geometry::index;
namespace bgm = boost::geometry::model;


typedef std::pair<double,double> L_Coor;
typedef std::pair<int , double> NeighborFF; //FF_ID,eDist
typedef std::pair<double,double> W_H_;

typedef bg::model::point<double, 2, bg::cs::cartesian> Point;
typedef std::pair<Point, int> PointWithID; //with FF_ID
typedef bgi::rtree< PointWithID, bgi::quadratic<P_PER_NODE> > RTree;

//define rtree for box
typedef bg::model::box<Point> Box;
typedef std::pair<Box, int> BoxWithID; //with FF_ID
typedef bgi::rtree< BoxWithID, bgi::quadratic<P_PER_NODE> > BoxTree;


double SE_Distance_ID(const L_Coor& p1, const PointWithID& p2);
double MH_Distance_ID(const L_Coor& p1, const PointWithID& p2);


double SE_Distance(const L_Coor& p1, const L_Coor& p2); //SquareEuclidean
double MH_Distance(const L_Coor& p1, const L_Coor& p2); //Manhattan
double Gaussian(const L_Coor& p1, const L_Coor& p2,const double bandwidth);




// Define a class for Pins
class Pin {
public:
    std::string name;
    double x, y;
    //add pin type:input, output or clock
    //set id for pin
    Pin(const std::string& name, double x, double y) : name(name), x(x), y(y) {}
};



// Define a class for Gates
class Gate {
public:

    
   
    Gate(const std::string& name, double x, double y) : name(name), x(x), y(y) {}

    /*
    void addPin(const Pin& pin) {
        pins.push_back(pin);
    }
    */
    void addPin(const std::string& pin_name, double x, double y) {
        L_Coor position;
        position.first = x;
        position.second = y;
        pins[name] = position;
    }

    void set_Gate_id(int i)
    {
        _Gate_id = i;
    }
    void set_Gate_type_id(int i)
    {
        _Gate_type_id = i;
    }
    void set_Gate_name(const std::string& n)
    {
        name = n;
    }
    void set_origin_coor(double a, double b)
    {
            _orginCoor.first = a;
            _orginCoor.second = b;
    }
private:
    int _Gate_id;
    int _Gate_type_id;
    std::string name;
    L_Coor _orginCoor;
    double x, y;  //width and height
    std::unordered_map<std::string, L_Coor> pins;
    //std::vector<Pin> pins;

};


// Define a class for Nets
class Net {
public:
    std::string name;
    std::vector<std::string> connectedPins;

    Net(const std::string& name) : name(name) {}

    void addPin(const std::string& pin) {
        connectedPins.push_back(pin);
    }

    //calculate MH distance for two pins
};

class placementRows {
public:
    double x1, y1, x2, y2;
    int num;

    placementRows(const double& a, const double& b, const double& c, const double& d, const int& e )
        : x1(a), y1(b), x2(c), y2(d), num(e) {}
};

#endif
