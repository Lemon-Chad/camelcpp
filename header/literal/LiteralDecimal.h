#ifndef CAMELCPP_LITERALDECIMAL_H
#define CAMELCPP_LITERALDECIMAL_H


class LiteralDecimal: public Value {
private:
    float value;

public:
    LiteralDecimal(float);

    float getValue() { return value; }

    Field* accessField(vector<string>) { return nullptr; }
    Field* createField(string, Value*) { return nullptr; }

    Value* performUnaryOperation(Operation::Operation);
    Value* performBinaryOperation(Operation::Operation, Value*);

    string toString();
};


#endif //CAMELCPP_LITERALDECIMAL_H
