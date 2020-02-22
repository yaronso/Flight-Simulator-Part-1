//
// Created by yaron on 13/12/2019.
//

#ifndef FLIGHTSIMULATOR_SLEEPCOMMAND_H
#define FLIGHTSIMULATOR_SLEEPCOMMAND_H

#include <vector>
#include <string>
#include "Command.h"

using namespace std;

class SleepCommand : public Command {
public:
    int execute(vector<string> stringVector, SymbolTable *symTable, int index);

    string doubleToString(double value);

    bool isString(string val);
};

#endif //FLIGHTSIMULATOR_SLEEPCOMMAND_H
