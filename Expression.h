//
// Created by adi on 10/11/2019.
//

#ifndef FLIGHTSIMULATOR_EXPRESSION_H
#define FLIGHTSIMULATOR_EXPRESSION_H

using namespace std;
/**
 * Expression Interface
 */
class Expression {

public:
    virtual double calculate() = 0;
    virtual ~Expression() {}
};

#endif //FLIGHTSIMULATOR_EXPRESSION_H