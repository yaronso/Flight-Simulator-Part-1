//
// Created by adi on 19/12/2019.
//

#ifndef FLIGHTSIMULATOR_LEXER_H
#define FLIGHTSIMULATOR_LEXER_H

#include "string"
#include "vector"
#include <sstream>

using namespace std;

class lexer {
private:
    string fileName;
public:
    lexer(string fileName);
    vector<string> runLexer();
    bool isOp(char c);
    bool isContainOp(string s);
};
#endif //FLIGHTSIMULATOR_LEXER_H


