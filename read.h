#ifndef _READ_H_
#define _READ_H_

#include "def.h"
#include "param.h"


void readFile(const std::string& filename, Param& param);

void writeOutput(const std::string& filename, std::vector<FF>& _FFs, std::map<std::string, std::string>& mappings);

#endif
