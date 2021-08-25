#ifndef CAMELCPP_LITERALINTEGER_H
#define CAMELCPP_LITERALINTEGER_H


class LiteralInteger: public Value {
private:
    int value;

public:
    LiteralInteger(int);

    int getValue() { return value; }

    Field* accessField(vector<string>) { return nullptr; }
    Field* createField(string, Value*) { return nullptr; }

    Value* performUnaryOperation(Operation::Operation);
    Value* performBinaryOperation(Operation::Operation, Value*);

    string toString();
};


#endif //CAMELCPP_LITERALINTEGER_H
