#include <sstream>
#include "printCommand.h"
#include "iostream"
#include "SymbolTable.h"
#include "Interpreter.h"

//
// Created by yaron on 15/12/2019.
//
int printCommand::execute(vector <string> stringVector, SymbolTable *symTable, int index) {
    // put in varName the string "Print" without the "..."
    string varName = stringVector[index + 2];
    //int indexFirst = index;
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
        cout << calc << endl; // print value of the variable v1

        // means it's not a variable - should print the input without the ""
    } else {
        // iterate over the string vector until the string endLine
        while (stringVector[endLineIndex] != "endLine") {
            endLineIndex++;
        }
        for (int i = startIndex; i < endLineIndex-1; i++) {
            string str = stringVector[i];
            if (i == startIndex) {
                str.erase(0, 1);
            }
            if (i==endLineIndex-2) {
                str.erase(str.size() - 1, 1);
            }
            cout << str << " ";
        }
        cout << " " << endl;
    }

    return endLineIndex + 1;
}

string printCommand::doubleToString(double calc) {
    ostringstream stringStream;
    stringStream << calc;
    string stringOfDoubleCalculation = stringStream.str();
    return stringOfDoubleCalculation;
}


bool printCommand::isString(string val) {
    string key = "\"";
    return val.compare(0, key.length(), key) == 0;
}