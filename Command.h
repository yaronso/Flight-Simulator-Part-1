//
// Created by adi on 12/12/2019.
//

#ifndef FLIGHTSIMULATOR_COMMAND_H
#define FLIGHTSIMULATOR_COMMAND_H

#include <mutex>
#include "Var.h"
#include "SymbolTable.h"
#include "DataReaderServer.h"

using namespace std;
extern bool closeClient_socket;
extern bool closeSocketftOpenDataServer;

/**
 * command Interface
 */
class Command {
public:
    virtual int execute(vector<string> stringVector, SymbolTable *symTable, int index) = 0;
    virtual  ~Command() = default;
};


#endif //FLIGHTSIMULATOR_COMMAND_H
