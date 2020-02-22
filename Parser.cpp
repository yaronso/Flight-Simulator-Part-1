//
// Created by adi on 16/12/2019.
//

#include "Parser.h"
#include "OpenDataServer.h"
#include "ConnectClientCommand.h"
#include "CreateVarCommand.h"
#include "SleepCommand.h"
#include "vector"
#include "SetCommand.h"
#include "printCommand.h"
#include "whileCommand.h"
#include "ifCommand.h"
#include "runFunctionCommand.h"
#include "createFunctionCommand.h"

void Parser::RunParser() {

    map<string, Command *> commandMap;
    // insert command to map
    commandMap["openDataServer"] = (new OpenDataServer());
    commandMap["connectControlClient"] = (new ConnectClientCommand());
    commandMap["var"] = (new CreateVarCommand());
    commandMap["Print"] = (new printCommand());
    commandMap["Sleep"] = (new SleepCommand());
    commandMap["while"] = (new whileCommand());
    commandMap["if"] = (new ifCommand());
    commandMap["If"] = (new ifCommand());


    unsigned int currentIndex = this->index;
    //commandOfSimulatorMap.put()
    while (currentIndex != stringVector.size()) {
        string currentString = stringVector.at(currentIndex);
        //dealing with command
        //Check if its a command that exists in commandMap
        if (commandMap.find(currentString) != commandMap.end()) {
            try {
                currentIndex = commandMap[currentString]->execute(stringVector, symbolTable, currentIndex);
            }
            catch (const char *e) {
                cout << e << endl;
            }
        } //   dealing with update var val;
        else if (symbolTable->varMap.find(currentString) != symbolTable->varMap.end()) {
            currentIndex = (new SetCommand())->execute(stringVector, symbolTable, currentIndex);

        } else if (symbolTable->functionMap.find(currentString) != symbolTable->functionMap.end()) {
            currentIndex = (new runFunctionCommand())->execute(stringVector,symbolTable,currentIndex);
        }
        else {
            currentIndex = (new createFunctionCommand())->execute(stringVector,symbolTable,currentIndex);
        }
    }
}

Parser::Parser(vector<string> stringVector1,
               SymbolTable *symbolTable1, int index1) {
    this->symbolTable = symbolTable1;
    this->stringVector = stringVector1;
    this->index = index1;
}

