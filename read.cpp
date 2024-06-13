#include "read.h"
void readFile(const std::string& filename, Circuit& circuit) {
    std::ifstream inFile(filename);

    if (!inFile) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }

    std::string line;
    while (std::getline(inFile, line)) {
        std::istringstream iss(line);
        std::string keyword;
        iss >> keyword;

        if (keyword == "Alpha" || keyword == "Beta" || keyword == "Gamma" || keyword == "Lambda" ||
            keyword == "BinWidth" || keyword == "BinHeight" || keyword == "BinMaxUtil" ||
            keyword == "DisplacementDelay") {
            double value;
            iss >> value;
            circuit.setParameter(keyword, value);
        } else if (keyword == "DieSize") {
            double x, y, width, height;
            iss >> x >> y >> width >> height;
            circuit.setDieSize(x, y, width, height);
        } else if (keyword == "NumInput") {
            int numInputs;
            iss >> numInputs;
        } else if (keyword == "Input") {
            std::string name;
            double x, y;
            iss >> name >> x >> y;
            circuit.addInput(Pin(name, x, y));
        } else if (keyword == "NumOutput") {
            int numOutputs;
            iss >> numOutputs;
        } else if (keyword == "Output") {
            std::string name;
            double x, y;
            iss >> name >> x >> y;
            circuit.addOutput(Pin(name, x, y));
        } else if (keyword == "FlipFlop") {
            int id;
            std::string name;
            double x, y;
            int numPins;
            iss >> id >> name >> x >> y >> numPins;
            
            FlipFlop* FF = new FlipFlop(id, name, x, y);
            for (int i = 0; i < numPins; ++i) {
                std::getline(inFile, line);
                std::istringstream pinStream(line);
                std::string pinKeyword, pinName;
                double pinX, pinY;
                pinStream >> pinKeyword >> pinName >> pinX >> pinY;
                FF->addPin(Pin(pinName, pinX, pinY));
            }
            circuit.addFlipFlop(name,FF);
        } else if (keyword == "Gate") {
            std::string name;
            double x, y;
            int numPins;
            iss >> name >> x >> y >> numPins;
            Gate* g = new Gate(name, x, y);
            for (int i = 0; i < numPins; ++i) {
                std::getline(inFile, line);
                std::istringstream pinStream(line);
                std::string pinKeyword, pinName;
                double pinX, pinY;
                pinStream >> pinKeyword >> pinName >> pinX >> pinY;
                g->addPin(Pin(pinName, pinX, pinY));
            }
            circuit.addGate(name,g);
        } else if (keyword == "Inst") {
            std::string name, type;
        
            double x, y;
            iss >> name >> type >> x >> y;
          
             if (type[0] !='G')
             {
                Instance _FF = Instance(name, type, x, y);

                _FF.is_FF = 1;
                //FF.id = circuit.FF_instances.size();
                _FF.FF = circuit.getFF(name);

                circuit.addInstance(_FF);
                circuit.addFFInstance(_FF);
             }
             else
             {
                Instance _gate =  Instance(name, type, x, y);

                _gate.is_FF = 0;
                //_gate.id = circuit.instances.size();
                _gate.gate = circuit.getGate(name);

                circuit.addInstance(_gate);
                 
             }
           
        } else if (keyword == "Net") {
            std::string name;
            int numPins;
            iss >> name >> numPins;
            Net net(name);
            for (int i = 0; i < numPins; ++i) {
                std::getline(inFile, line);
                std::istringstream pinStream(line);
                std::string pinKeyword, pinName;
                pinStream >> pinKeyword >> pinName;
                net.addPin(pinName);
            }
            circuit.addNet(net);
        } else if (keyword == "QpinDelay"){
            std::string name;
            double value;
            iss >> name >> value;
            circuit.setQpinDelay(name, value);
        } else if (keyword == "TimingSlack"){
            std::string name, pin;
            double value;
            iss >> name >> pin >>value;
            circuit.setTimingSlack(name, value);
        } else if (keyword == "GatePower"){
            std::string name;
            double value;
            iss >> name >> value;
            circuit.setGatePowers(name, value);
        } else if (keyword == "PlacementRows"){
            int number;
            double x1, y1, x2, y2;
            iss >> x1 >> y1 >> x2 >> y2 >> number;
            placementRows row(x1, y1, x2, y2, number);
            circuit.setPlacementRows(row);
        }

    }

    inFile.close();
}

void writeOutput(const std::string& filename, const std::vector<Instance>& newInstances, const std::map<std::string, std::vector<std::string>>& mappings) {
    std::ofstream outFile(filename);

    if (!outFile) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }

    outFile << "CellInst " << newInstances.size() << "\n";
    for (const auto& instance : newInstances) {
        outFile << "Inst " << instance.name << " " << instance.type << " " << instance.x << " " << instance.y << "\n";
    }

    for (const auto& mapping : mappings) {
          std::string in = mapping.first;
          std::vector<std::string> pins = mapping.second;
          for (const auto& pin : pins)
          {
              outFile << in << " map " << pin << "\n";
          }


    }

    outFile.close();
}

