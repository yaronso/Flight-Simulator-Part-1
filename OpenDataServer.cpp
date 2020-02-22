//
// Created by yaron on 13/12/2019.
//
#include <iostream>
#include <string>
#include <vector>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <thread>
#include "OpenDataServer.h"
#include "Interpreter.h"

bool closeSocketftOpenDataServer = false;

// open a data server and then call a thread to run it.
int OpenDataServer::execute(vector<string> stringVector, SymbolTable *symTable, int index) {
    int PortNum;
    string varName = stringVector[index + 2];
    int startIndex = index + 2;
    int endLineIndex = index + 2;
    bool boolString = isString(varName);
    // if the var is not a string
    if (!boolString) {
// iterate over the string vector until the string endLine
        while (stringVector[endLineIndex] != "endLine") {
            endLineIndex++;
        }
        // the string result will holds the expression we would like to print
        string result = "";
        for (int i = startIndex; i < endLineIndex - 1; i++) {
            result.append(stringVector[i]);
        }

        Interpreter *arithmeticInt = new Interpreter();
        // the following loop inserts the simPathToValFromSimMap from the varMap of our symTable
        // inside the varaibles of the interpreter
        for (auto const &x : symTable->varMap) {
            string var = x.first;
            string val = doubleToString(x.second->value);
            arithmeticInt->setVariables(var + "=" + val);
        }

        double calc = arithmeticInt->interpret(result)->calculate();
        string stringOfDoubleCalculation = doubleToString(calc);
        PortNum = stoi(stringOfDoubleCalculation);
    }
        //if its a string
    else {
        // save the number that was inputed
        string str = stringVector[index];
        str.erase(0, 1);
        str.erase(str.size() - 1, 1);
        PortNum = stoi(str);
    }
    //create socket
    int socketfd = socket(AF_INET, SOCK_STREAM, 0);
    if (socketfd == -1) {
        //error
        throw "Could not create a socket";
    }

    //bind socket to IP address
    // we first need to create the sockaddr obj.
    sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY; //give me any IP allocated for my machine
    address.sin_port = htons(PortNum);
    //we need to convert our number
    // to a number that the network understands.


    //the actual bind command
    if (bind(socketfd, (struct sockaddr *) &address, sizeof(address)) == -1) {
        throw "Could not bind the socket to an IP";
    }

//making socket listen to the port
    if (listen(socketfd, 5) == -1) { //can also set to SOMAXCON (max connections)
        throw "Error during listening command";
        return -3;
    } else {
        std::cout << "Server is now listening ..." << std::endl;
    }

    // accepting a client
    int client_socket = accept(socketfd, (struct sockaddr *) &address,
                               (socklen_t *) &address);

    if (client_socket == -1) {
        throw "Error accepting client";
    }

    close(socketfd); //closing the listening socket

    thread serverThread(readFromSimulator, symTable, client_socket);
    serverThread.detach();
    return index + 5;
}


void readFromSimulator(SymbolTable *symTable, int client_socket) {
    vector<double> simulatorValues(36);
    vector<double>::iterator it = simulatorValues.begin();
    string firstBuffer = "";
    bool run = true;
    while (run) {
        //reading from client
        char buffer[1024] = {0};
        read(client_socket, buffer, 1024);
        string secondBuffer = buffer;
        firstBuffer = firstBuffer + secondBuffer;
        string firstPart = firstBuffer.substr(0, firstBuffer.find("\n")); //all tha values from start to \n
        int startSecondPart = firstBuffer.find("\n") + 1;
        string secondPart = firstBuffer.substr(
                startSecondPart, firstBuffer.length()); //all the values from \n to end
        //split the values by ","
        stringstream ss(firstPart);
        string valStr;
        while (getline(ss, valStr, ',')) {
            double doubleVal = stod(valStr);
            *it = doubleVal;
            it++;
        }
        //insert the left values to the next iteration
        firstBuffer = secondBuffer;
        //if we got 36 values we will update the symTable
        if (it == simulatorValues.end()) {
            for (int j = 1; j <= 36; j++) {
                // for each index we lock & unlock
                //if the path exist in simMap we need to update his value;
                string currentPath = symTable->indexFromXmlToValMap[j];
                //if the path exist in simMap we need to update his value;
                if (symTable->simMap.find(currentPath) != symTable->simMap.end()) {
                    double newVal = simulatorValues.at(j - 1);
                    string stringDouble = OpenDataServer::doubleToString(newVal);
                    symTable->mutex.lock();
                    symTable->simMap[currentPath]->value = newVal;
                    symTable->mutex.unlock();
                }
            }
            it = simulatorValues.begin();
        }
        if (closeSocketftOpenDataServer) {
            close(client_socket);
        }
    }
}


string OpenDataServer::doubleToString(double calc) {
    ostringstream stringStream;
    stringStream << calc;
    string stringOfDoubleCalculation = stringStream.str();
    return stringOfDoubleCalculation;
}

bool OpenDataServer::isString(string val) {
    string key = "\"";
    return val.compare(0, key.length(), key) == 0;
}