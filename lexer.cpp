//
// Created by adi on 19/12/2019.
//
#include "string"
#include "vector"
#include "lexer.h"
#include "fstream"
#include "lexer.h"

vector<string> lexer::runLexer() {
    vector<string> stringVector;
    ifstream file;
    file.open(fileName, ios::in);
    if (!file.is_open()) {
        throw "can not find file";
    }
    string word;
    string line;
    while (getline(file, line)) {
        istringstream iss(line);
        while (iss >> word) {

            //if the word contains ( or ) we need to split it
            if ((word.find("(") < word.size())
                | (word.find(")") < word.size())) {
                string splitWord = "";
                for (auto x :word) {
                    if ((x == '(') || x == ')') {
                        string temp(1, x);

                        if (splitWord != "") {
                            stringVector.push_back(splitWord);
                            splitWord = "";
                        }
                        stringVector.push_back(temp);}
                        //stringVector.push_back(splitWord);
                        //splitWord = "";
//                    } else if (x == '"') {
//                        continue;
//                    }
                        else {
                            splitWord = splitWord + x;
                        }
                    }
                    if (splitWord != "") {
                        stringVector.push_back(splitWord);
                    }
                    splitWord = "";
                    //if the word contains operators without spaces between them
                } else if (isContainOp(word)) {
                    string splitword2 = "";
                    char prevChar = '.';
                    for (auto x:word) {
                        if (isOp(x)) {
                            if (splitword2 != "") {
                                //if the operator is not the first char we will insert all the prev string to the vector
                                stringVector.push_back(splitword2);
                                splitword2 = "";
                            }
                            string stringX(1, x);
                            //we will also insert the operator to the vector
                            //if the prev is also op;
                            if (isOp(prevChar)) {
                                //if the prev char is also op we need to combine them
                                int ind = stringVector.size();
                                string newOP = stringVector.at(ind - 1);
                                stringVector.back() = newOP.append(stringX);
                            } else {
                                //if the prev char is not op we insert the current op
                                stringVector.push_back(stringX);
                            }
                        } else {
                            splitword2 = splitword2 + x;
                        }
                        prevChar = x;
                    }
                    if (splitword2 != "") {
                        stringVector.push_back(splitword2);
                    }
                    //for regular words
                } else {
                    stringVector.push_back(word);
                }
            }
            stringVector.push_back("endLine");
            //restart the current line command;
        }
        file.close();
        return stringVector;
    }


    lexer::lexer(string
    fileName1) {
        this->fileName = fileName1;
    }

    bool lexer::isOp(char c) {
        char arrOp[] = {'<', '>', '=', '/', '*', '+', '-', '{', '}'};
        int arraySize = sizeof(arrOp) / sizeof(char);
        for (int i = 0; i < arraySize; i++) {
            if (arrOp[i] == c) {
                return true;
            }
        }
        return false;
    }

    bool lexer::isContainOp(string s) {
        string arrOp[] = {"<", ">", "=", "/", "*", "+", "-", "{", "}"};
        for (int i = 0; i < 9; i++) {
            if (s.find(arrOp[i]) < s.size()) {
                return true;
            }
        }
        return false;
    }
