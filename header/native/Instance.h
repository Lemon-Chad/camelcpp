#ifndef CAMELCPP_INSTANCE_H
#define CAMELCPP_INSTANCE_H

#include <string>

class Instance: public Value {
private:
    RuntimeEnvironment environment;
    RuntimeContext* internalContext;

public:
    Instance(RuntimeEnvironment &, RuntimeContext* &);

    Field* accessField(vector<string>);
    Field* createField(string, Value*);

    Value* performUnaryOperation(Operation::Operation);
    Value* performBinaryOperation(Operation::Operation, Value*);

    string toString();
};


#endif //CAMELCPP_INSTANCE_H
