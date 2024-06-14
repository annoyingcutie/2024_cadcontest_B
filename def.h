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

typedef std::pair<double,double> L_Coor;
typedef std::pair<double,double> W_H_;
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
};

class placementRows {
public:
    double x1, y1, x2, y2;
    int num;

    placementRows(const double& a, const double& b, const double& c, const double& d, const int& e )
        : x1(a), y1(b), x2(c), y2(d), num(e) {}
};

#endif
