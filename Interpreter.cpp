#include "Interpreter.h"
#include <string>
#include "ex1.h"
#include "Expression.h"
#include "stack"
#include "map"
#include <list>
#include <iostream>

using namespace std;

bool Interpreter::isInt(char c) {
    return (c >= '0') && (c <= '9');
}

bool Interpreter::isLetter(char c) {
    return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');
}

Expression *Interpreter::interpret(string string1) {
    createStack(string1);
    return this->exp1;
}

bool Interpreter::isOperator(string s) {
    if (s.compare("+") == 0) { return true; }
    else if (s.compare("-") == 0) { return true; }
    else if (s.compare("/") == 0) { return true; }
    else if (s.compare("*") == 0) { return true; }
    else if (s.compare("(") == 0) { return true; }
    else if (s.compare("U-") == 0) { return true; }
    else if (s.compare("U+") == 0) { return true; }
    else return s.compare(")") == 0;
}

string Interpreter::getString(char x) {
    string s(1, x);
    return s;
}

list<string> Interpreter::createArray(string string1) {

    //creating array of saperet strings from the original string
    unsigned int i = 0; //iterator for string
    unsigned long stringSize = string1.size();

    list<string> arr;
    while (i < stringSize) {

        if (isOperator(getString(string1[i]))) {
            if ((i == 0) && (compareStr(getString(string1[i]), "-"))) {
                arr.push_back("U-");
                i++;
            } else if ((i == 0) && (compareStr(getString(string1[i]), "+"))) {
                arr.push_back("U+");
                i++;
            } else if ((compareStr(getString(string1[i]), "-")) &&
                       (compareStr(getString(string1[i - 1]), "("))) {

                arr.push_back("U-");
                i++;

            } else if ((compareStr(getString(string1[i]), "+")) &&
                       (compareStr(getString(string1[i - 1]), "("))) {

                arr.push_back("U+");
                i++;

            } else {
                arr.push_back(getString(string1[i]));
                i++;
            }

        } else {
            string temps;
            while (!isOperator(getString(string1[i])) && i < stringSize) {
                temps.append(getString(string1[i]));
                i++;
            }
            arr.push_back(temps);
        }
    }

    return arr;
}

bool Interpreter::isAritmathic(string s) {
    if (compareStr(s, "+") || compareStr(s, "-") || compareStr(s, "/") || compareStr(s, "*") || compareStr(s, "U-") ||
        compareStr(s, "U+")) {
        return true;
    } else {
        return false;
    }
}

void Interpreter::createStack(string string1) {

    list<string> listOfStrings = createArray(string1);
    stack<Expression *> expStack;
    stack<string> opStack;

    map<string, int> map;
    map.insert(pair<string, int>("+", 10));
    map.insert(pair<string, int>("-", 10));
    map.insert(pair<string, int>("/", 20));
    map.insert(pair<string, int>("*", 20));
    map.insert(pair<string, int>("(", 100));
    map.insert(pair<string, int>("U-", 10));
    map.insert(pair<string, int>("U+", 10));

    string prevElement = "";
    while (!listOfStrings.empty()) {
        string currentElement = listOfStrings.front();
        //checking input validity
        if (isOperator(prevElement)) {
            if (isOperator(currentElement)) {
                if ((compareStr(prevElement, "(")) &&
                    ((compareStr(currentElement, "*")) || (compareStr(currentElement, "/")))) {
                    throw "invalid input";
                }
                if ((compareStr(currentElement, ")")) && (isAritmathic(prevElement))) {
                    throw "invalid input";
                }
                if ((isAritmathic(currentElement)) && (isAritmathic(prevElement))) {
                    throw "invalid input";
                }
            }
        }
        if (listOfStrings.size() == 1 && isAritmathic(currentElement)) {
            throw "invalid input";
        }
        prevElement = listOfStrings.front();

        if (!isOperator(listOfStrings.front())) {
            //check if its an operator
            if (this->VariableMap.count(listOfStrings.front()) == 1) {
                double num = VariableMap.at(listOfStrings.front());
                if (num < 0.0) {
                    num = num * (-1);
                    Expression *e = new Value(num);
                    expStack.push(new UMinus(e));
                } else {
                    expStack.push(new Value(num));
                }
                listOfStrings.pop_front();
            } else if (checkIfValidNumber(listOfStrings.front())) {
                expStack.push(new Value(stod(listOfStrings.front())));
                listOfStrings.pop_front();
            } else {
                throw "invalid input";
            }
        } else {
            //handle with plus or minus for unary operators
            //if (compareStr(listOfStrings.front(), "+") || (compareStr(listOfStrings.front(), "-"))) {
            //  InsertUnaryOperators(listOfStrings, opStack);
            //}
            //handle with expresion between ()
            if (compareStr(listOfStrings.front(), ")")) {
                while (!compareStr(opStack.top(), "(")) {
                    if (opStack.empty()) {
                        throw "invalid input";
                    } else {
                        createAndInsertToStackTheExpressions(expStack, opStack);

                    }
                }
                //remove the ( and )
                listOfStrings.pop_front();
                opStack.pop();
            } else {
                int opFromString = map[listOfStrings.front()];;
                if (opStack.empty()) {
                    opStack.push(listOfStrings.front());
                    listOfStrings.pop_front();
                } else {
                    int opFRomStack = map[opStack.top()];
                    if (opFromString <= opFRomStack) {
                        //bags with the u minus
                        createAndInsertToStackTheExpressions(expStack, opStack);
                        opStack.push(listOfStrings.front());
                        listOfStrings.pop_front();
                    } else {
                        opStack.push(listOfStrings.front());
                        listOfStrings.pop_front();
                    }
                }
            }
        }
    }
    // if there are more operators in the operators stack
    while (!opStack.empty()) {
        if (compareStr(opStack.top(), "(")) {
            throw "invalid input";
        }
        createAndInsertToStackTheExpressions(expStack, opStack);
    }
    this->exp1 = expStack.top();
    return;
}

bool Interpreter::compareStr(string str1, string str2) {
    return str1.compare(str2) == 0;
}

void Interpreter::createAndInsertToStackTheExpressions(stack<Expression *> &expStack, stack<string> &opStack) {
    if (opStack.top().compare("+") == 0) {
        Expression *right = expStack.top();
        expStack.pop();
        Expression *left = expStack.top();
        expStack.pop();
        expStack.push(new Plus(left, right));
        opStack.pop();
    } else if (opStack.top().compare("-") == 0) {
        Expression *right = expStack.top();
        expStack.pop();
        Expression *left = expStack.top();
        expStack.pop();
        expStack.push(new Minus(left, right));
        opStack.pop();
    } else if (opStack.top().compare("/") == 0) {
        Expression *right = expStack.top();
        expStack.pop();
        Expression *left = expStack.top();
        expStack.pop();
        expStack.push(new Div(left, right));
        opStack.pop();
    } else if (opStack.top().compare("*") == 0) {
        Expression *right = expStack.top();
        expStack.pop();
        Expression *left = expStack.top();
        expStack.pop();
        expStack.push(new Mul(left, right));
        opStack.pop();
    } else if (opStack.top().compare("U+") == 0) {
        Expression *exp = expStack.top();
        expStack.pop();
        expStack.push(new UPlus(exp));
        opStack.pop();
    } else if (opStack.top().compare("U-") == 0) {
        Expression *exp = expStack.top();
        expStack.pop();
        expStack.push(new UMinus(exp));
        opStack.pop();
    }
}

void Interpreter::setVariables(string str) {
    string str2 = str;
    string pair;
    while (!str2.empty()) {
        int found = str2.find(";");
        if (found == -1) {
            pair = str2;
            insertToMap(pair);
            str2 = "";
        } else {
            pair = str2.substr(0, found);
            insertToMap(pair);
            str2 = str2.substr(found + 1, str2.length() - pair.length());
        }
    }
}

void Interpreter::insertToMap(const string &pairStr) {
    int found = pairStr.find('=');
    string name = pairStr.substr(0, found);
    checkIfValidName(name);
    string num = pairStr.substr(found + 1);
    checkIfValidNumber(num);
    this->VariableMap[name] = stod(num);
}

bool Interpreter::checkIfValidNumber(string number) {
    int point = 0;
    //if not starting and ending with int
    if (((!isInt(number[0])) && (number[0] != '-')) || (!isInt(number[number.length() - 1]))) {
        throw "invalid input number";
    }
    //check all letters are number or point
    string stringMinusFirstChar = number.substr(1, number.length() - 1);
    for (char c:stringMinusFirstChar) {
        if (c == '.') {
            point = point + 1;
        }
        //remove this checking - the simulator return value like this 7.6e-05
        //if ((!isInt(c)) && (c != '.')) {
        // cout<< " invalid here "<< number<<endl;
        //      throw "invalid input number - problem number 2";
        //  }
}
//check there is only one point
if (point > 1) {
throw "invalid input";
}
return true;
}

bool Interpreter::checkIfValidName(string name) {

    if ((!isLetter(name[0])) && (name[0] != '_')) {
        throw "invalid input";
    }

    for (char c:name) {
        if ((!isLetter(c)) && (!isInt(c)) && c != '_') {
            throw "invalid input";
        }
    }
    return true;
}