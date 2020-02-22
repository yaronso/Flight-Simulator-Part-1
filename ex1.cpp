
#include <string>
#include "ex1.h"
#include "Expression.h"

using namespace std;

/** variable class*/
Variable &Variable::operator++() {
    this->value = value + 1;
    return *this;
}

Variable &Variable::operator+=(double left) {
    this->value = value + left;
    return *this;

}

Variable &Variable::operator--() {
    this->value = value - 1;
    return *this;

}

Variable &Variable::operator-=(double left) {
    this->value = value - left;
    return *this;

}

Variable &Variable::operator++(int) {
    this->value++;
    return *this;

}

Variable &Variable::operator--(int) {
//#pragma clang diagnostic pop
    this->value = this->value - 1;
    return *this;
}

double Variable::calculate() {
    return this->value;
}

Variable::~Variable() {
}

/** binary operators*/
double Plus::calculate() {
    return (this->left->calculate() + this->right->calculate());
}

Plus::Plus(Expression *l, Expression *r) {
    this->right = r;
    this->left = l;
}

Plus::~Plus() {
    delete this->right;
    delete this->left;
}

double Minus::calculate() {
    return (this->left->calculate() - this->right->calculate());
}

Minus::Minus(Expression *l, Expression *r) {
    this->left = l;
    this->right = r;
}

Minus::~Minus() {
    delete this->right;
    delete this->left;
}

double Mul::calculate() {
    return this->left->calculate() * this->right->calculate();
}

Mul::Mul(Expression *l, Expression *r) {
    this->right = r;
    this->left = l;
}

Mul::~Mul() {
    delete this->right;
    delete this->left;
}

double Div::calculate() {
    //return error id divide in 0;
    if (right->calculate() == 0) {
        throw "division by zero!";
    } else {
        return (this->left->calculate() / this->right->calculate());
    }
}

Div::Div(Expression *l, Expression *r) {
    this->left = l;
    this->right = r;

}

Div::~Div() {
    delete this->right;
    delete this->left;

}

/** value class*/
double Value::calculate() {
    return this->val;
}




UPlus::UPlus(Expression *exp1) {
    this->exp = exp1;

}

UPlus::~UPlus() {
    delete this->exp;
}

double UPlus::calculate() {
    return this->exp->calculate();
}

UMinus::UMinus(Expression *exp1) {
    this->exp = exp1;
}

UMinus::~UMinus() {
    delete this->exp;
}

double UMinus::calculate() {
    return ((-1) * this->exp->calculate());
}
