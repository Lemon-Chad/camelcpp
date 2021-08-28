#ifndef CAMELCPP_FUNCTION_H
#define CAMELCPP_FUNCTION_H

#include <vector>
#include <string>

using namespace std;


class Function: public Value {

public:
    virtual Value* invokeFunction(RuntimeEnvironment &, vector<Value *> &) = 0;

    Field* accessField(vector<string>) override { return nullptr; }
    Field* createField(string, Value*) override { return nullptr; }

    Value* performUnaryOperation(Operation::Operation) override { throw "UnsupportedOperation"; }
    Value* performBinaryOperation(Operation::Operation, Value*) override { throw "UnsupportedOperation"; }

    string toString() override { return "CamelFunction"; }
};


#endif //CAMELCPP_FUNCTION_H
