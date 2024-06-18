#include "read.h"
#include <boost/algorithm/string.hpp>

void readFile(const std::string& filename, Param& param) {
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
             std::cout<<keyword<<std::endl;
            double value;
            iss >> value;
            param.setParameter(keyword, value);
        } else if (keyword == "DieSize") {
             std::cout<<keyword<<std::endl;
            double x, y, width, height;
            iss >> x >> y >> width >> height;
            param.setDieSize(x, y, width, height);
        } else if (keyword == "NumInput") {
             std::cout<<keyword<<std::endl;
            int numInputs;
            iss >> numInputs;
        } else if (keyword == "Input") {
            std::cout<<keyword<<std::endl;
            std::string name;
            double x, y;
            iss >> name >> x >> y;
            param.addInput(Pin(name, x, y));
        } else if (keyword == "NumOutput") {
             std::cout<<keyword<<std::endl;
            int numOutputs;
            iss >> numOutputs;
        } else if (keyword == "Output") {
            std::cout<<keyword<<std::endl;
            std::string name;
            double x, y;
            iss >> name >> x >> y;
            param.addOutput(Pin(name, x, y));
        } else if (keyword == "FlipFlop") {
            std::cout<<keyword<<std::endl;
            int id;
            std::string name;
            double x, y;
            int numPins;
            iss >> id >> name >> x >> y >> numPins;

            FF FlipFlop = FF(id, name, x, y);
            for (int i = 0; i < numPins; ++i) {
                std::getline(inFile, line);
                std::istringstream pinStream(line);
                std::string pinKeyword, pinName;
                double pinX, pinY;
                pinStream >> pinKeyword >> pinName >> pinX >> pinY;
                
                FlipFlop.addPin(pinName, pinX, pinY);
            }
            param.add_FF_List(name, FlipFlop);
        } else if (keyword == "Gate") {
            std::cout<<keyword<<std::endl;
            std::string name;
            double x, y;
            int numPins;
            iss >> name >> x >> y >> numPins;
            Gate g = Gate(name, x, y);
            for (int i = 0; i < numPins; ++i) {
                std::getline(inFile, line);
                std::istringstream pinStream(line);
                std::string pinKeyword, pinName;
                double pinX, pinY;
                pinStream >> pinKeyword >> pinName >> pinX >> pinY;
                g.addPin(pinName, pinX, pinY);
            }
            param.addGate(name,g);
        } else if (keyword == "Inst") {
            std::cout<<keyword<<std::endl;
            std::string name, type;
        
            double x, y;
            iss >> name >> type >> x >> y;
          
             if (type[0] !='G')
             {
                int l = param.get_FF_id(type);
                FF temp_FF = param.getFF(l); 
                temp_FF.set_Iname(name);
                temp_FF.set_orginCoor(x,y);
                param.addFFInstance(temp_FF);
               
             }
             else
             {
                int l = param.get_Gate_id(type);
                Gate temp_gate = param.getGate(l);
                temp_gate.set_Gate_name(name);
                temp_gate.set_origin_coor(x,y);
                param.addGateInstance(temp_gate);
                 
             }
           
        } else if (keyword == "Net") {
            std::cout<<keyword<<std::endl;
            std::string name;
            int numPins;
            iss >> name >> numPins;
            Net net(name);
            std::string source;
            for (int i = 0; i < numPins; ++i) {
                std::getline(inFile, line);
                std::istringstream pinStream(line);
                std::string pinKeyword, pinName;
                pinStream >> pinKeyword >> pinName;
                net.addPin(pinName);
                
                if(i == 0) { source = pinName;}
                else
                {
                    
    
                    std::string inst_name, inst_pin;

                    std::string sample = pinName;
                    std::vector<std::string> strs;
                    boost::split(strs, sample, boost::is_any_of("/"));
                    if(strs.size() == 2)
                    {
                        inst_name = strs[0];
                        inst_pin = strs[1];
                        //std::cout << "setting clock" <<inst_name <<inst_pin <<std::endl;
                        if(inst_pin == "CLK" || inst_pin == "clk")
                    {
                        //std::cout << "setting clock" <<std::endl;
                        param.set_clock_source(inst_name,source);
                        //std::cout << "setting clock finish" <<std::endl;
                    }

                    }

                    
                   
        
                   // std::istringstream nameStream(pinName);
                   // std::getline(nameStream, inst_name, '/');
                   // std::getline(nameStream, inst_pin, '/');

                    
                }


               
            }
            param.addNet(net);

           

        } else if (keyword == "QpinDelay"){
            std::cout<<keyword<<std::endl;
            std::string name;
            double value;
            iss >> name >> value;
            param.setQpinDelay(name, value);
        } else if (keyword == "TimingSlack"){
            std::cout<<keyword<<std::endl;
            std::string name, pin;
            double value;
            iss >> name >> pin >>value;
            param.setTimingSlack(name, value);
        } else if (keyword == "GatePower"){
            std::cout<<keyword<<std::endl;
            std::string name;
            double value;
            iss >> name >> value;
            param.setGatePowers(name, value);
        } else if (keyword == "PlacementRows"){
            std::cout<<keyword<<std::endl;
            int number;
            double x1, y1, x2, y2;
            iss >> x1 >> y1 >> x2 >> y2 >> number;
            placementRows row(x1, y1, x2, y2, number);
            param.setPlacementRows(row);
            /*
            Initialize the 2D vector by the number
            */
        }
        
       

    }
    std::cout<<"updating..."<<std::endl;
    param.update_q_s();
    std::cout<<"Meanshifting..."<<std::endl;
    param.doMeanShift();
    param.printFFs();
    std::cout<<"Finish Meanshifting..."<<std::endl;

    inFile.close();

    

}

/*
void writeOutput(const std::string& filename, const std::vector<FF>& _FFs, const std::map<std::string, std::string>& mappings) {
    std::ofstream outFile(filename);

    if (!outFile) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }

    outFile << "CellInst " << _FFs.size() << "\n";
    for (const auto& instance : _FFs) {
        outFile << "Inst " << instance.get_Inst_name() << " " << instance.get_type_name() << " " << instance.get_x_coor() << " " << instance.get_y_coor() << "\n";
    }

    for (const auto& mapping : mappings) {
          std::string before = mapping.first;
          std::string after = mapping.second;
         outFile << before << " map " << after << "\n";
    }

    outFile.close();
}
*/

