//
// Created by adi on 15/12/2019.
//
#include <iostream>
#include <string>
#include <vector>
#include "CreateVarCommand.h"
#include "Var.h"
#include "Interpreter.h"



int CreateVarCommand::execute(vector<string> stringVector,SymbolTable *symTable, int index) {
    index = index + 1;
    //int thisScope = scope;
    string varName = stringVector.at(index);
    index = index + 1;
    string op = stringVector.at(index);
    if (op == "=") {
        int endLineIndex = index + 1;
        while(stringVector[endLineIndex]!="endLine"){
            endLineIndex++;
        }
        string result = "";
        for(int i=index+1 ; i<endLineIndex ; i++){
            result.append(stringVector[i]);
        }
        Interpreter* arithmeticInt = new Interpreter();
        //arithmeticInt -> setVariables();
        for (auto const& x : symTable->varMap)
        {
            string var = x.first;
            string val = doubleToString(x.second->value);
            arithmeticInt->setVariables(var+"="+val);
        }
        //calculate the expression
        double calc = arithmeticInt->interpret(result)->calculate();
        // make a string from the double calculation
        Var *newVar = new Var(varName, calc, false, "");
        symTable->mutex.lock();
        symTable->varMap.insert({varName, newVar});
        symTable->mutex.unlock();
        return endLineIndex + 1;
    }
    index = index + 3;
    string simVal = stringVector.at(index);
    simVal.erase(0,2);
    simVal.erase(simVal.size()-1,1);

    if (op == "->") {
        Var *newVar = new Var(varName, 0, true, simVal);
        //the app need to update the simulator
        //*(symTable->simMap).insert({varName,newVar});
        symTable->mutex.lock();
        symTable->varMap.insert({varName, newVar});
        symTable->mutex.unlock();
        index = index + 3;
        return index;
    } else {//if (op == "<-") {
        Var *newVar = new Var(varName, 0, false, simVal);
        //the simulator need to update the app
        symTable->mutex.unlock();
        symTable->simMap.insert({simVal, newVar});
        symTable->varMap.insert({varName, newVar});
        symTable->mutex.unlock();
        index = index + 3;
        return index;
    }

}

string CreateVarCommand::doubleToString(double calc)  {
    ostringstream stringStream;
    stringStream << calc;
    string stringOfDoubleCalculation = stringStream.str();
    return stringOfDoubleCalculation;
}