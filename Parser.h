//
// Created by adi on 12/12/2019.
//

#ifndef FLIGHTSIMULATOR_PARSER_H
#define FLIGHTSIMULATOR_PARSER_H

#include "Command.h"
#include "Var.h"
#include "SymbolTable.h"
#include "DataReaderServer.h"
#include "map"
#include "string"
#include "vector"
using namespace std;

class Parser {
    SymbolTable* symbolTable;
    vector<string> stringVector;
    DataReaderServer *dataReaderServer;
    int index;
    //int scope;

public:
    Parser(vector<string> stringVector1, SymbolTable* symbolTable, int index1);
    void RunParser();
};
#endif //FLIGHTSIMULATOR_PARSER_H

