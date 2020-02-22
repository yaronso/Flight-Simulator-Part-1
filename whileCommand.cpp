#include <sstream>
#include "Command.h"
#include "whileCommand.h"
#include "Interpreter.h"
#include "Parser.h"
#include "SymbolTable.h"

//
// Created by yaron on 15/12/2019.
//
int whileCommand::execute(vector<string> stringVector, SymbolTable *symTable, int index) {
    int indexFindOperator;
    int indexSulSul;
    int indexCloseSulSul;
    int whileIndex = index;
    string isOper = "";

    // run over the first line of the while until the {
    while (stringVector.at(index) != "{") {
        if (isOperator(stringVector.at(index))) {
            indexFindOperator = index;
            isOper = stringVector.at(indexFindOperator);
        }
        index++;
    }
    indexSulSul = index;

    string expLeft = "";
    string expRight = "";
    // for the left expression
    for (int i = whileIndex + 1; i < indexFindOperator; i++) {
        expLeft.append(stringVector[i]);
    }
    // for the right expression
    for (int j = indexFindOperator + 1; j < indexSulSul; j++) {
        expRight.append(stringVector[j]);
    }

    Interpreter *arithmeticLeft = new Interpreter();
    Interpreter *arithmeticRight = new Interpreter();

    for (auto const &x : symTable->varMap) {
        string var = x.first;
        string val = doubleToString(x.second->value);
        arithmeticLeft->setVariables(var + "=" + val);
        arithmeticRight->setVariables(var + "=" + val);
    }

    // first we calculate each expression
    double calcLeft = arithmeticLeft->interpret(expLeft)->calculate();
    double calcRight = arithmeticRight->interpret(expRight)->calculate();
    int sign = isOperatorFlag(isOper);

    vector<string> whileVector;
    int j = indexSulSul + 2;
    while (stringVector.at(j) != "}") {
        whileVector.push_back(stringVector.at(j));
        j++;
    }
    indexCloseSulSul = j;

    // check if the condition of the while is true
    switch (sign) { ;
        case 1:
            while (calcLeft < calcRight) {
                // call parser
                Parser *whileParser = new Parser(whileVector, symTable, 0);
                whileParser->RunParser();
                updateVarMap(symTable, arithmeticLeft, arithmeticRight);
                calcLeft = arithmeticLeft->interpret(expLeft)->calculate();
                calcRight = arithmeticRight->interpret(expRight)->calculate();
                this_thread::sleep_for(std::chrono::seconds(2));

            }
            break;
        case 2:
            while (calcLeft > calcRight) {
                // call parser
                Parser *whileParser = new Parser(whileVector, symTable, 0);
                whileParser->RunParser();
                updateVarMap(symTable, arithmeticLeft, arithmeticRight);
                calcLeft = arithmeticLeft->interpret(expLeft)->calculate();
                calcRight = arithmeticRight->interpret(expRight)->calculate();
                this_thread::sleep_for(std::chrono::seconds(2));
            }
            break;
        case 3:
            while (calcLeft <= calcRight) {
                // call parser
                Parser *whileParser = new Parser(whileVector, symTable, 0);
                whileParser->RunParser();
                updateVarMap(symTable, arithmeticLeft, arithmeticRight);
                calcLeft = arithmeticLeft->interpret(expLeft)->calculate();
                calcRight = arithmeticRight->interpret(expRight)->calculate();
                this_thread::sleep_for(std::chrono::seconds(2));

            }
            break;
        case 4:
            while (calcLeft >= calcRight) {
                // call parser
                Parser *whileParser = new Parser(whileVector, symTable, 0);
                whileParser->RunParser();
                updateVarMap(symTable, arithmeticLeft, arithmeticRight);
                calcLeft = arithmeticLeft->interpret(expLeft)->calculate();
                calcRight = arithmeticRight->interpret(expRight)->calculate();
                this_thread::sleep_for(std::chrono::seconds(2));

            }
            break;
        case 5:
            while (calcLeft == calcRight) {
                // call parser
                Parser *whileParser = new Parser(whileVector, symTable, 0);
                whileParser->RunParser();
                updateVarMap(symTable, arithmeticLeft, arithmeticRight);
                calcLeft = arithmeticLeft->interpret(expLeft)->calculate();
                calcRight = arithmeticRight->interpret(expRight)->calculate();
                this_thread::sleep_for(std::chrono::seconds(2));
            }
            break;
        case 6:
            while (calcLeft != calcRight) {
                // call parser
                Parser *whileParser = new Parser(whileVector, symTable, 0);
                whileParser->RunParser();
                updateVarMap(symTable, arithmeticLeft, arithmeticRight);
                calcLeft = arithmeticLeft->interpret(expLeft)->calculate();
                calcRight = arithmeticRight->interpret(expRight)->calculate();
                this_thread::sleep_for(std::chrono::seconds(2));
            }
            break;
    }
    return indexCloseSulSul + 2;
}

void
whileCommand::updateVarMap(const SymbolTable *symTable, Interpreter *arithmeticLeft, Interpreter *arithmeticRight) {
    for (auto const &x : symTable->varMap) {
        string var = x.first;
        string val = doubleToString(x.second->value);
        arithmeticLeft->setVariables(var + "=" + val);
        arithmeticRight->setVariables(var + "=" + val);
    }

}

int whileCommand::isOperatorFlag(string s) {
    if (s.compare("<") == 0) { return 1; }
    else if (s.compare(">") == 0) { return 2; }
    else if (s.compare("<=") == 0) { return 3; }
    else if (s.compare(">=") == 0) { return 4; }
    else if (s.compare("==") == 0) { return 5; }
    else if (s.compare("!=") == 0) { return 6; }
    else {
        throw "Error in isOperatorFlag Func in WhileCommnand";
    }
}

bool whileCommand::isOperator(string s) {
    if (s.compare("<") == 0) { return true; }
    else if (s.compare(">") == 0) { return true; }
    else if (s.compare("<=") == 0) { return true; }
    else if (s.compare(">=") == 0) { return true; }
    else if (s.compare("=") == 0) { return true; }
    else if (s.compare("!=") == 0) { return true; }
    else { return false; }
}

string whileCommand::doubleToString(double calc) {
    ostringstream stringStream;
    stringStream << calc;
    string stringOfDoubleCalculation = stringStream.str();
    return stringOfDoubleCalculation;
}