//
// Created by yaron on 16/12/2019.
//

#ifndef FLIGHTSIMULATOR_DATAREADERSERVER_H
#define FLIGHTSIMULATOR_DATAREADERSERVER_H
#include <map>
#include <string>
#include <exception>
#include <sstream>
#include <iostream>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <vector>
#include <thread>

using namespace std;
#include <map>
using namespace std;
class SymbolTable;
class DataReaderServer {
public:
    map<string, double> simPathToValFromSimMap; // the same map as indexFromXmlToValMap we just opposite the order
    map<int, string> indexFromXmlToValMap;  // int: 1 - 23 , string: the simulator strings
public:
    DataReaderServer();
    void printXML();
};

#endif //FLIGHTSIMULATOR_DATAREADERSERVER_H
