//
// Created by adi on 15/12/2019.
//

#ifndef FLIGHTSIMULATOR_CONNECTCLIENTCOMMAND_H
#define FLIGHTSIMULATOR_CONNECTCLIENTCOMMAND_H


#include <vector>
#include <string>
#include <netinet/in.h>
#include "Command.h"

using namespace std;
class ConnectClientCommand: public Command {
public:
    sockaddr_in address;
    int client_socket;
    int execute(vector<string> stringVector,SymbolTable* symTable, int index);
    vector<std::string> split(const string &text, char sep);
};
void writeToSimulator(SymbolTable *symTable, int simulatorClient);

#endif //FLIGHTSIMULATOR_CONNECTCLIENTCOMMNAD_H