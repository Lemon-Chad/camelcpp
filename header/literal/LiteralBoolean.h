#ifndef CAMELCPP_LITERALBOOLEAN_H
#define CAMELCPP_LITERALBOOLEAN_H

#include <string>

class LiteralBoolean: public Value {
private:
    bool value;

public:
    LiteralBoolean(bool);

    bool getValue() { return value; }

    Field* accessField(vector<string>) { return nullptr; }
    Field* createField(string, Value*) { return nullptr; }

    Value* performUnaryOperation(Operation::Operation);
    Value* performBinaryOperation(Operation::Operation, Value*);

    string toString();
};


#endif //CAMELCPP_LITERALBOOLEAN_H
