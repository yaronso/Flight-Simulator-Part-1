#include <sstream>
#include "ifCommand.h"
#include "Interpreter.h"
#include "Parser.h"

//
// Created by yaron on 18/12/2019.
//
int ifCommand::execute(vector<string> stringVector, SymbolTable *symTable, int index) {
    int indexFindOperator;
    int indexOpenSulSul;
    int indexCloseSulSul;
    int ifIndex = index;
    string operatorString = "";

    // run over the first line of the if until the {            example: if (rpm < 2) {
    while(stringVector.at(index) != "{") {
        if(isOperator(stringVector.at(index))) {
            indexFindOperator = index;
            operatorString = stringVector.at(indexFindOperator);
        }
        index++;
    }
    indexOpenSulSul = index;

    string expLeft = "";
    string expRight = "";
    // for the left expression of the if
    for(int i = ifIndex + 1 ; i < indexFindOperator; i++){
        expLeft.append(stringVector[i]);
    }
    // for the right expression of the if
    for(int j = indexFindOperator + 1 ; j < indexOpenSulSul; j++) {
        expRight.append(stringVector[j]);
    }

    Interpreter* arithmeticLeft = new Interpreter();
    Interpreter* arithmeticRight = new Interpreter();

    for (auto const& x : symTable->varMap) {
        string var = x.first;
        string val = doubleToString(x.second->value);
        arithmeticLeft->setVariables(var + "=" + val);
        arithmeticRight->setVariables(var + "=" + val);
    }

    // first we calculate each expression
    double calcLeft = arithmeticLeft->interpret(expLeft)->calculate();
    double calcRight = arithmeticRight->interpret(expRight)->calculate();
    int sign = isOperatorFlag(operatorString);

    // create a vector of strings for the scope of the if
    vector<string> ifVector;
    int j = indexOpenSulSul + 2;  // changed because of the endline
    // iterate over the scope of the if between { ... }
    while(stringVector.at(j) != "}") {
        ifVector.push_back(stringVector.at(j));
        j++;
    }
    indexCloseSulSul = j;

    // check if the condition of the if is true
    switch (sign) { ;
        case 1:
            while (calcLeft < calcRight) {
                // call parser
                Parser* ifParser = new Parser(ifVector, symTable, index);
                ifParser->RunParser();
                updateVarMap(symTable, arithmeticLeft, arithmeticRight);
            }
            break;
        case 2:
            while (calcLeft > calcRight) {
                // call parser
                Parser* ifParser = new Parser(ifVector,  symTable, index);
                ifParser->RunParser();
                updateVarMap(symTable, arithmeticLeft, arithmeticRight);
            }
            break;
        case 3:
            while (calcLeft <= calcRight) {
                // call parser
                Parser *ifParser = new Parser(ifVector,  symTable, index);
                ifParser->RunParser();
                updateVarMap(symTable, arithmeticLeft, arithmeticRight);
            }
            break;
        case 4:
            while (calcLeft >= calcRight) {
                // call parser
                Parser* ifParser = new Parser(ifVector,  symTable, index);
                ifParser->RunParser();
                updateVarMap(symTable, arithmeticLeft, arithmeticRight);
            }
            break;
        case 5:
            while (calcLeft == calcRight) {
                // call parser
                Parser* ifParser = new Parser(ifVector,  symTable, index);
                ifParser->RunParser();
                updateVarMap(symTable, arithmeticLeft, arithmeticRight);
            }
            break;
        case 6:
            while (calcLeft != calcRight) {
                // call parser
                Parser* ifParser = new Parser(ifVector,   symTable, index);
                ifParser->RunParser();
                updateVarMap(symTable, arithmeticLeft, arithmeticRight);
            }
            break;
    }

    return indexCloseSulSul + 2;
}

void ifCommand::updateVarMap(const SymbolTable *symTable, Interpreter *arithmeticLeft, Interpreter *arithmeticRight) {
    for (auto const &x : symTable->varMap) {
        string var = x.first;
        string val = doubleToString(x.second->value);
        arithmeticLeft->setVariables(var + "=" + val);
        arithmeticRight->setVariables(var + "=" + val);
    }
  }

int ifCommand::isOperatorFlag(string s) {
    if (s.compare("<") == 0) { return 1; }
    else if (s.compare(">") == 0) { return 2; }
    else if (s.compare("<=") == 0) { return 3; }
    else if (s.compare(">=") == 0) { return 4; }
    else if (s.compare("==") == 0) { return 5; }
    else {//if(s.compare("!=") == 0 ){
        return 6; }

}

bool ifCommand::isOperator(string s) {
    if (s.compare("<") == 0) { return true; }
    else if (s.compare(">") == 0) { return true; }
    else if (s.compare("<=") == 0) { return true; }
    else if (s.compare(">=") == 0) { return true; }
    else if (s.compare("=") == 0) { return true; }
    else if(s.compare("!=") == 0 ){ return true;  }
    else {
        return false;
    }
}

string ifCommand::doubleToString(double calc)  {
    ostringstream stringStream;
    stringStream << calc;
    string stringOfDoubleCalculation = stringStream.str();
    return stringOfDoubleCalculation;
}