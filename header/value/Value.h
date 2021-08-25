//
// Created by Myles Harris on 8/23/21.
//

#ifndef CAMELCPP_VALUE_H
#define CAMELCPP_VALUE_H

#include "../Operation.h"
#include "../runtime/Field.h"


class Field;

class Value {
public:
    virtual Field* accessField(vector<string>) = 0;
    virtual Field* createField(string, Value*) = 0;

    virtual Value* performUnaryOperation(Operation::Operation) = 0;
    virtual Value* performBinaryOperation(Operation::Operation, Value*) = 0;

    virtual string toString() = 0;
};


#endif //CAMELCPP_VALUE_H
