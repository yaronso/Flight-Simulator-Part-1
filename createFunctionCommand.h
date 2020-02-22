//
// Created by adi on 29/12/2019.
//

#ifndef FLIGHTSIMULATOR_CREATEFUNCTIONCOMMAND_H
#define FLIGHTSIMULATOR_CREATEFUNCTIONCOMMAND_H

#include "Command.h"
#include "vector"

using namespace std;

class createFunctionCommand: public Command {
public:
    int execute(vector<string> stringVector, SymbolTable *symTable, int index);
};

#endif //FLIGHTSIMULATOR_CREATEFUNCTIONCOMMAND_H

