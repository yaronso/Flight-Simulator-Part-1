//
// Created by adi on 10/11/2019.
//

#ifndef EX1_EX1_H
#define EX1_EX1_H

#include "Expression.h"
#include <string>
#include <cstdio>
#include "Interpreter.h"

/** binary operators*/
class BinaryOperator : public Expression {
protected:
    Expression *right;
    Expression *left;
public:
    virtual double calculate() = 0;
};

class Plus : public BinaryOperator {
public:
    Plus(Expression *r, Expression *l);

    ~Plus();

    double calculate();
};

class Minus : public BinaryOperator {
public:
    Minus(Expression *r, Expression *l);

    ~Minus();

    double calculate();
};

class Mul : public BinaryOperator {
public:
    Mul(Expression *r, Expression *l);

    ~Mul();

    double calculate();
};

class Div : public BinaryOperator {
public:
    Div(Expression *r, Expression *l);

    ~Div();

    double calculate();
};


/**value class*/
class Value : public Expression {
private:
    const double val;
public:
    Value(double v) : val(v) {}
    double calculate();
};

/** unary operator*/
class UnaryOperator : public Expression {
protected:
    Expression *exp;
public:
    virtual double calculate() = 0;
};

class UPlus : public UnaryOperator {
public:
    UPlus(Expression *exp);

    ~UPlus();

    double calculate();
};

class UMinus : public UnaryOperator {
public:
    UMinus(Expression *exp);

    ~UMinus();

    double calculate();
};

class Variable : public Expression {
    double calculate();

    std::string name;
    double value;
public:
    Variable(std::string n, double val) {
        this->name = n;
        this->value = val;
    }
    ~Variable();

    Variable &operator++();

    Variable &operator--();

    Variable &operator++(int num);

    Variable &operator--(int num);

    Variable &operator+=(double left);

    Variable &operator-=(double left);

};

#endif //EX1_EX1_H
