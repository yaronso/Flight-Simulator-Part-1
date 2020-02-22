//
// Created by adi on 29/12/2019.
//

#include <algorithm>
#include "runFunctionCommand.h"
#include "string"
#include "Parser.h"

int runFunctionCommand::execute(vector<string> stringVector, SymbolTable *symTable, int index) {
    string functionName = stringVector.at(index);
    string FunctionVarValue = stringVector.at(index + 2);
    vector<string> functionVector = symTable->functionMap[functionName];
    int varIndex = 0;
    while (functionVector.at(varIndex) != "var") {
        varIndex += 1;
    }
    string functionVarName = functionVector.at(varIndex + 1);
    //replace the var name to the var value
    replace(functionVector.begin(), functionVector.end(), functionVarName, FunctionVarValue);
    int openingIndex = 0;
    int closingIndex = 0;
    int numOfStartParenthesis = 1;
    int numOfEndParenthesis = 0;
    //dealing with internal scope
    while (functionVector.at(openingIndex) != "{") {
        openingIndex += 1;
    }
    closingIndex = openingIndex + 1;
    while (numOfStartParenthesis != numOfEndParenthesis) {
        if (functionVector.at(closingIndex) == "{") {
            numOfStartParenthesis += 1;
        }
        if (functionVector.at(closingIndex) == "}") {
            numOfEndParenthesis += 1;
        }
        closingIndex += 1;;
    }
    //create new vector that we will send to the parser command
    vector<string> vectorForParser;
    for (int i = openingIndex+2; i <= closingIndex-2; i++) {
        vectorForParser.push_back(functionVector.at(i));
    }
    //run the parser on the function vector
    Parser *functionParser = new Parser(vectorForParser, symTable, 0);
    functionParser->RunParser();
    return index + 5;
}

