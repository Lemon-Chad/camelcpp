#ifndef CAMELCPP_LITERALRETURN_H
#define CAMELCPP_LITERALRETURN_H

#include <string>

class LiteralReturn: public Value {
private:
    Value* value;

public:
    LiteralReturn(Value* &);

    Value* getValue() { return value; }

    Field* accessField(vector<string>);
    Field* createField(string, Value*);

    Value* performUnaryOperation(Operation::Operation);
    Value* performBinaryOperation(Operation::Operation, Value*);

    string toString();
};


#endif //CAMELCPP_LITERALRETURN_H
