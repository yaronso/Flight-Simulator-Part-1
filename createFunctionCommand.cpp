//
// Created by adi on 29/12/2019.
//

#include "createFunctionCommand.h"

int createFunctionCommand::execute(vector<string> stringVector, SymbolTable *symTable, int index) {
    string functionName = stringVector.at(index);
    int numOfEndParenthesis =0;
    index = index+1;
    //vector of strings inside the function
    vector<string> functionVector;
    //put the index after the "{" sign
    while (stringVector.at(index) != "{"){
        functionVector.push_back(stringVector.at(index));
        index=index+1;
    }
    functionVector.push_back(stringVector.at(index));
    //used to know if there is an internal scope
    int numOfStartParenthesis =1;
    index = index+1;
    while(numOfStartParenthesis!=numOfEndParenthesis){
        if(stringVector.at(index) == "{"){
            numOfStartParenthesis+=1;
        }
        if(stringVector.at(index) == "}"){
            numOfEndParenthesis+=1;
        }
        functionVector.push_back(stringVector.at(index));
        index+=1;
    }
    //insert the string to the vector
    functionVector.push_back(stringVector.at(index));
    symTable->functionMap[functionName]= functionVector;
    return index+1;
}

