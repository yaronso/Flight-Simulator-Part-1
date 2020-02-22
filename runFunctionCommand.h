//
// Created by adi on 29/12/2019.
//

#ifndef FLIGHTSIMULATOR_RUNFUNCTIONCOMMAND_H
#define FLIGHTSIMULATOR_RUNFUNCTIONCOMMAND_H

#include "Command.h"

using namespace std;

class runFunctionCommand : public Command {
public:
    int execute(vector<string> stringVector, SymbolTable *symTable, int index);

};

#endif //FLIGHTSIMULATOR_RUNFUNCTIONCOMMAND_H

