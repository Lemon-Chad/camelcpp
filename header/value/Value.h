#ifndef CAMELCPP_VALUE_H
#define CAMELCPP_VALUE_H

#include "../Operation.h"
#include "../runtime/Field.h"
#include "../runtime/RuntimeEnvironment.h"
#include "../runtime/RuntimeContext.h"


class Field;
class RuntimeEnvironment;
class RuntimeContext;

class Value {
public:
    virtual Field* accessField(vector<string>) = 0;
    virtual Field* createField(string, Value*) = 0;

    virtual Value* performUnaryOperation(Operation::Operation) = 0;
    virtual Value* performBinaryOperation(Operation::Operation, Value*) = 0;

    virtual string toString() = 0;
};


#endif //CAMELCPP_VALUE_H
