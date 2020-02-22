//
// Created by adi on 15/12/2019.
//

#include <sstream>
#include <mutex>
#include "SetCommand.h"
#include "Interpreter.h"
std::mutex mutex1;
int SetCommand::execute(vector<string> stringVector, SymbolTable *symTable, int index) {

    string varName = stringVector[index];
    if (symTable->varMap.find(varName) != symTable->varMap.end()) {
        Var* v1 = (symTable->varMap)[varName];
        index = index + 2;
        int endLineIndex = index + 1;
        while(stringVector[endLineIndex]!="endLine"){
            endLineIndex++;
        }
        string result = "";
        for(int i=index ; i<endLineIndex ; i++){
            result.append(stringVector[i]);
        }
        Interpreter* arithmeticInt = new Interpreter();
        for (auto const& x : symTable->varMap)
        {
            string var = x.first;
            string val = doubleToString(x.second->value);
            arithmeticInt->setVariables(var+"="+val);
        }
        // calculate the expression
        double calc = arithmeticInt->interpret(result)->calculate();
        // make a string from the double calculation
        string stringOfDoubleCalculation = doubleToString(calc);
        // for debug
        //cout << calc << endl;
        //update value
        symTable->mutex.lock();
        v1->value=calc;
        if (v1->varUpdateSim) {
            string simPath = v1->sim;
           // simPath.erase(0,1);
            // we need to update the var in the simulator to the new value
            string sim1 = "set ";
            sim1.append(simPath);
            sim1.append(" ");
            sim1.append(stringOfDoubleCalculation);
            sim1.append("\r\n");
            string val = sim1;
            //writing back to client
            //add the value we need to update in the sim to the queue
            //we will update it in the connect command
            symTable->QueueSetValToSim.push(val);
            symTable->mutex.unlock();
        }
        symTable->mutex.unlock();
        //v1->updateVal(stringOfDoubleCalculation,symTable);
        // unlock the mutex after updating
        //symTable->mutex.unlock();
        return endLineIndex + 1;
        //symTable->mutex.unlock();
    }
    else {
        throw "not valid command";
    }
}

string SetCommand::doubleToString(double calc)  {
    ostringstream stringStream;
    stringStream << calc;
    string stringOfDoubleCalculation = stringStream.str();
    return stringOfDoubleCalculation;
}

