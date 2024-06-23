#ifndef _FF_H_
#define _FF_H_

#include "def.h"



class FF{
public:
     FF(int bits, const std::string& name, double x, double y) : _bits(bits), name(name)
    { _w_h_.first = x;
      _w_h_.second = y;
      _cid = -1;
      _h = 0;
      _isShifting = true;
    }
    void set_FF_id(int i){_FF_id = i;}
    void set_type_id(int i){_type_id = i;}
    int get_FF_id()const{ return _FF_id;}
    int get_FF_type_id()const{return _type_id;}

    void set_QpinDelay(double Q){_QpinDelay = Q;}
    double get_QpinDelay()const { return _QpinDelay;}

    void set_TimingSlack(double S){_TimingSlack = S;}
    double get_TimingSlack()const{return _TimingSlack; }
    
    void set_Power(double P){ _Power = P;}
    double get_Power()const {return _Power;}

    void addPin(const std::string& pin_name, double x, double y) {
        L_Coor position;
        position.first = x;
        position.second = y;
        _pins[name] = position;
    }
    void set_Iname(std::string n)
    {
        Instance_name = n;
    }
    void set_orginCoor(double x, double y)
    {
        _orginCoor.first = x;
        _orginCoor.second = y;
        _Coor = _orginCoor;
    }

    double getX()const {return _Coor.first;}
    double getY()const {return _Coor.second;}
    double getOrigX()const{return _orginCoor.first;}
    double getOrigY()const{return _orginCoor.second;} 
    double getW()const{return _w_h_.first;}
    double getH()const{return _w_h_.second;}
    L_Coor& getCoor() {return _Coor;}
    L_Coor& getOrinCoor() {return _orginCoor;}

    int getBits()const{return _bits;}

    std::string get_Inst_name(){return Instance_name;}
    std::string get_type_name(){return name;}
    void set_type_name(std::string s){ name = s;}

    bool isShifting()const {return _isShifting;}
    double getBandwidth()const {return _h;}

    void setClusterID(int c_id){_cid = c_id;}
    void setShifting(bool t) {_isShifting = t;}

    void addNeighbor    (int id, double dis) {_neighbors.emplace_back(id, dis);}
    void setCoor        (double x, double y)   {_Coor.first = x; _Coor.second = y;}
    void setCoor        (L_Coor& coor)           {_Coor = coor;} 
   
    int  getNeighborSize()const {return (int)_neighbors.size();}
    
    NeighborFF& getNeighbor(int i) {return _neighbors[i];}
    void print ();
    void sortNeighbors  ();
    void setBandWidth   ();

    void setClock(std::string source) {_clock = source;}
    std::string get_CLK() {return _clock;}
    //void setPin();

    double  doShifting (); //return eDist
private:
    int _type_id;
    int _FF_id;
    int _cid;
    int _bits;
    std::string name; //FF type
    std::string Instance_name;
    L_Coor _orginCoor;
    L_Coor _Coor;
    W_H_ _w_h_;
    std::unordered_map<std::string, L_Coor> _pins;
    //std::vector<Pins> _pins;
    double _QpinDelay;
    double _TimingSlack;
    double _Power;

    double _h;
    bool _isShifting;

    std::vector<NeighborFF> _neighbors;

    std::string _clock = "empty"; 

    


    



};

#endif
