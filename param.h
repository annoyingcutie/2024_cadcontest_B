#ifndef _PARAM_H_
#define _PARAM_H_

#include "def.h"
#include "FF.h"

class Param{

public:

     void add_FF_List(const std::string& name, FF& flipFlop) {
        int l = _FF_list.size();
        _FF_list_map[name] = l ;
        flipFlop.set_type_id(l);
        _FF_list.push_back(flipFlop);
    }
    int get_FF_id(const std::string& type)
    {
        return _FF_list_map[type];
    }
   
    int get_Gate_id(const std::string& type)
    {
        return _Gate_list_map[type];
    }
    FF getFF(const int& Id)
    {
        return _FF_list[Id];
    }
    void addGate(const std::string& name, Gate& gate) {
        int l = _Gate_list.size();
       _Gate_list_map[name] = l ;
       gate.set_Gate_type_id(l);
       _Gate_list.push_back(gate);
    }
    Gate getGate(const int& Id)
    {
        return _Gate_list[Id];
    }

    void addNet(const Net& net) {
        nets.push_back(net);
        /*
        std::vector<std::string> p = net.connectedPins;
        std::string in = p[0];
        for (int i = 1;i < p.size(); i++)
        {
            mappings[in].push_back(p[i]);
        }
        */

    }


    void addFFInstance(FF& flipflop) {
        int l = _FFInstance.size();
        flipflop.set_FF_id(l);
        std::string s = flipflop.get_Inst_name();
        _FF_Inst_map[s] = flipflop.get_FF_id();
        _FFInstance.push_back(flipflop);
    }

    void addGateInstance(Gate& g) {
        int l = _gateInstance.size();
        g.set_Gate_id(l);
        
        _gateInstance.push_back(g);
    }

    void addInput(const Pin& input) {
        inputs.push_back(input);
    }

    void addOutput(const Pin& output) {
        outputs.push_back(output);
    }

    void setParameter(const std::string& key, double value) {
        _costParameters[key] = value;
    }
    /*
    void setParameter(const std::string& key, double value) {
        parameters[key] = value;
    }
    */
    void setDieSize(double x, double y, double width, double height) {
        _diePos.first= x;
        _diePos.second = y;
        _dieWH.first = width;
        _dieWH.second = height;
    }
    void setQpinDelay(std::string name, double value)
    {
        int index_list = _FF_list_map[name];
        FF temp_FF = getFF(index_list);
        temp_FF.set_QpinDelay(value);
        _FF_list[index_list] = temp_FF;
        //qpinDelays[name] = value;
    }
    void setTimingSlack(std::string name, double value)
    {
        int index_list = _FF_Inst_map[name];
        FF temp_FF = _FFInstance[index_list];
        temp_FF.set_TimingSlack(value);
        _FFInstance[index_list] = temp_FF;
        //timingSlacks[name] = value;
    }
    void setGatePowers(std::string name, double value)
    {
        int index_list = _FF_list_map[name];
        FF temp_FF = getFF(index_list);
        temp_FF.set_Power(value);
        _FF_list[index_list] = temp_FF;
        //gatePowers[name] = value;
    }
    void setPlacementRows(const placementRows& row)
    {
       p_row.push_back(row); 
    }
  
    void update_q_s()
    {
        for (int i = 0; i < _FFInstance.size();i++)
        {
            int temp_FF_tid = _FFInstance[i].get_FF_type_id(); //Get type ID
            
            FF temp_F = _FF_list[temp_FF_tid];
            double p = temp_F.get_power();
            double Q = temp_F.get_Qpin();
            _FFInstance[i].set_Power(p);
            _FFInstance[i].set_QpinDelay(Q);
            
        }
    }

    std::vector<FF> _FFInstance;
    std::map<std::string, std::string> mappings;
private:
    
    std::unordered_map<std::string, double> _costParameters;
    L_Coor _diePos;
    W_H_ _dieWH;
    std::vector<Pin> inputs;
    std::vector<Pin> outputs;
    int _FF_List_num = 0;
    std::unordered_map<std::string, int> _FF_list_map;
    std::vector<FF> _FF_list;

    std::unordered_map<std::string, int> _FF_Inst_map;

    std::unordered_map<std::string, int> _Gate_list_map;
    std::vector<Gate> _Gate_list;

    std::vector<Gate> _gateInstance;
    //std::vector<FF> _FFInstance;

    std::vector<placementRows> p_row;
    std::vector<Net> nets;
    
};

#endif

