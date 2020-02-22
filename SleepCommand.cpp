//
// Created by yaron on 13/12/2019.
//
#include <iostream>
#include <string>
#include <vector>
#include "SleepCommand.h"
#include "Interpreter.h"
#include <thread>

int SleepCommand::execute(vector<string> stringVector, SymbolTable *symTable, int index) {
    index = index + 2;
    // put in varName the string Sleep without the
    string varName = stringVector[index];
    //int indexFirst = index;
    int startIndex = index;
    int endLineIndex = index;
    bool boolString = isString(varName);
    // if the var is not a string
    if (!boolString) {
        // iterate over the string vector until the string endLine
        while(stringVector[endLineIndex] != "endLine") {
            endLineIndex++;
        }
        // the string result will holds the expression we would like to print
        string result = "";
        for(int i = startIndex ; i < endLineIndex-1 ; i++) {
            result.append(stringVector[i]);
        }

        Interpreter* arithmeticInt = new Interpreter();
        // the following loop inserts the simPathToValFromSimMap from the varMap of our symTable
        // inside the varaibles of the interpreter
        for (auto const& x : symTable->varMap) {
            string var = x.first;
            string val = doubleToString(x.second->value);
            arithmeticInt->setVariables(var + "=" + val);
        }

        double calc = arithmeticInt->interpret(result)->calculate();
        string stringOfDoubleCalculation = doubleToString(calc);
        int res = calc;
        std::this_thread::sleep_for(std::chrono::milliseconds(res));
        return endLineIndex + 1;
    // means it's a string
    } else {
        // save the number that was inputed
        string str = stringVector[index];
        str.erase(0, 1);
        str.erase(str.size()-1,1);
        int milis = stoi(str);
        // sleep command
        std::this_thread::sleep_for(std::chrono::milliseconds(milis));
        index = index + 3;
        return index;
    }

}

string SleepCommand::doubleToString(double calc) {
    ostringstream stringStream;
    stringStream << calc;
    string stringOfDoubleCalculation = stringStream.str();
    return stringOfDoubleCalculation;
}

bool SleepCommand::isString(string val){
    string key ="\"";
    return val.compare(0, key.length(), key) == 0;
}

