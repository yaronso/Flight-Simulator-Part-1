//
// Created by adi on 12/11/2019.
//

#ifndef FLIGHTSIMULATOR_INTERPRETER_H
#define FLIGHTSIMULATOR_INTERPRETER_H


#include "Expression.h"
#include <string>
#include <list>
#include <cstdio>
#include "stack"
#include "map"
#include "queue"

class Interpreter {
private:
    map<string, double> VariableMap;
    Expression *exp1;
public:
    Expression *interpret(string);

    void createStack(string);

    list <string> createArray(string);

    string getString(char);

    bool compareStr(string, string);

    bool isInt(char);

    bool isLetter(char);

    void createAndInsertToStackTheExpressions(stack<Expression *> &expStack, stack <string> &opStack);

    static bool isOperator(string);

    void setVariables(string);

    void insertToMap(const string &basicString);

    bool checkIfValidNumber(string);

    bool checkIfValidName(string);

    bool isAritmathic(string s);
};


#endif //FLIGHTSIMULATOR_INTERPRETER_H
