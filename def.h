#ifndef _DEF_H_
#define _DEF_H_


#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <string>
#include <map>

// Define a class for Pins
class Pin {
public:
    std::string name;
    double x, y;

    Pin(const std::string& name, double x, double y) : name(name), x(x), y(y) {}
};

// Define a class for FlipFlops
class FlipFlop {
public:
    int id;//id = bits
    std::string name;
    double x, y; //x=width, y=height
    std::vector<Pin> pins;
    

    FlipFlop(int id, const std::string& name, double x, double y) : id(id), name(name), x(x), y(y) {}

    void addPin(const Pin& pin) {
        pins.push_back(pin);
    }
};

// Define a class for Gates
class Gate {
public:
    std::string name;
    double x, y;
    std::vector<Pin> pins;

    Gate(const std::string& name, double x, double y) : name(name), x(x), y(y) {}

    void addPin(const Pin& pin) {
        pins.push_back(pin);
    }
};

// Define a class for Instances
class Instance {
public:
    std::string name;
    std::string type;
    double x, y;
    double width, height;
    int id;

    Instance(const std::string& name, const std::string& type, double x, double y)
        : name(name), type(type), x(x), y(y) {}
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

// Define a class for the entire Circuit
class Circuit {
public:
    std::unordered_map<std::string, double> parameters;
    double dieSize[4];
    std::vector<Pin> inputs;
    std::vector<Pin> outputs;
    std::vector<FlipFlop> flipFlops;
    std::vector<Gate> gates;
    std::vector<Instance> FF_instances;
    std::vector<Instance> instances;
    std::vector<placementRows> p_row;
    std::vector<Net> nets;
    std::map<std::string, std::vector<std::string>> mappings;
    std::unordered_map<std::string, double> qpinDelays;
    std::unordered_map<std::string, double> timingSlacks;
    std::unordered_map<std::string, double> gatePowers;

    void addFlipFlop(const FlipFlop& flipFlop) {
        flipFlops.push_back(flipFlop);
    }

    void addGate(const Gate& gate) {
        gates.push_back(gate);
    }

    void addNet(const Net& net) {
        nets.push_back(net);
        std::vector<std::string> p = net.connectedPins;
        std::string in = p[0];
        for (int i = 1;i < p.size(); i++)
        {
            mappings[in].push_back(p[i]);
        }

    }


    void addInstance(const Instance& instance) {
        instances.push_back(instance);
    }

    void addFFInstance(const Instance& instance) {
        FF_instances.push_back(instance);
    }

    void addInput(const Pin& input) {
        inputs.push_back(input);
    }

    void addOutput(const Pin& output) {
        outputs.push_back(output);
    }

    void setParameter(const std::string& key, double value) {
        parameters[key] = value;
    }

    void setDieSize(double x, double y, double width, double height) {
        dieSize[0] = x;
        dieSize[1] = y;
        dieSize[2] = width;
        dieSize[3] = height;
    }
    void setQpinDelay(std::string name, double value)
    {
        qpinDelays[name] = value;
    }
    void setTimingSlack(std::string name, double value)
    {
        timingSlacks[name] = value;
    }
    void setGatePowers(std::string name, double value)
    {
        gatePowers[name] = value;
    }
    void setPlacementRows(const placementRows& row)
    {
       p_row.push_back(row); 
    }
};

#endif
