using namespace std;
#include "read.h"
#include "def.h"

int main(int argc, char* argv[]) {
    Circuit circuit;
    std::string inputFilename = argv[1];
    std::string outputFilename = argv[2];

    readFile(inputFilename, circuit);


    // Example new instances and mappings (these should be determined by your specific requirements)
    /*
    std::vector<Instance> newInstances = {
        Instance("C5", "FF2", 20.0, 10.0),
        Instance("C6", "FF1", 20.0, 0.0)
    };

    std::vector<std::pair<std::string, std::string>> mappings = {
        {"C1/D", "C6/D"},
        {"C1/Q", "C6/Q"},
        {"C1/CLK", "C6/CLK"},
        {"C2/D", "C5/D1"},
        {"C2/Q", "C5/Q1"},
        {"C2/CLK", "C5/CLK"},
        {"C3/D", "C5/D0"},
        {"C3/Q", "C5/Q0"}
    };
    */
    writeOutput(outputFilename, circuit.instances,  circuit.mappings);

    return 0;
};

