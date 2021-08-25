#ifndef CAMELCPP_LITERALSTRING_H
#define CAMELCPP_LITERALSTRING_H


class LiteralString: public Value {
private:
    string value;

public:
    LiteralString(string);

    string getValue() { return value; }

    Field* accessField(vector<string>) { return nullptr; }
    Field* createField(string, Value*) { return nullptr; }

    Value* performUnaryOperation(Operation::Operation);
    Value* performBinaryOperation(Operation::Operation, Value*);

    string toString();
};


#endif //CAMELCPP_LITERALSTRING_H
