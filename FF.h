#ifndef _FF_H_
#define _FF_H_

#include "def.h"


class FF{


   

public:
     FF(int bits, const std::string& name, double x, double y) : _bits(bits), name(name)
    { _w_h_.first = x;
      _w_h_.second = y;
    }
    void set_FF_id(int i)
    {
        _FF_id = i;
    }
    void set_type_id(int i)
    {
        _type_id = i;
    }
    int get_FF_id()
    {
        return _FF_id;
    }
    int get_FF_type_id()
    {
        return _type_id;
    }
    void set_QpinDelay(double Q)
    {
        _QpinDelay = Q;
    }
    void set_TimingSlack(double S)
    {
        _TimingSlack = S;
    }
    void set_Power(double P)
    {
        _Power = P;
    }
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
    }
    std::string get_Inst_name(){return Instance_name;}
    std::string get_type_name(){return name;}
    double get_x_coor(){return _orginCoor.first;}
    double get_y_coor(){return _orginCoor.second;}


    double get_power(){ return _Power; }
    double get_Qpin(){ return _QpinDelay;}

  
    
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

    



};

#endif
