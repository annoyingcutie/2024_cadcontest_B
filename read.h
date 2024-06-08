#ifndef _READ_H_
#define _READ_H_

#include "def.h"

void readFile(const std::string& filename, Circuit& circuit);

void writeOutput(const std::string& filename, const std::vector<Instance>& newInstances, const std::map<std::string, std::vector<std::string>>& mappings);


#endif
