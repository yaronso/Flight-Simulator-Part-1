//
// Created by yaron on 15/12/2019.
//

#ifndef FLIGHTSIMULATOR_PRINTCOMMAND_H
#define FLIGHTSIMULATOR_PRINTCOMMAND_H

#include "Command.h"

class printCommand : public Command  {
public:
    int execute(vector<string> stringVector, SymbolTable *symTable, int index);
    string doubleToString(double calc);

    bool isString(string val);
};
#endif //FLIGHTSIMULATOR_PRINTCOMMAND_H
