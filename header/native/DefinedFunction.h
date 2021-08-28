#ifndef CAMELCPP_DEFINEDFUNCTION_H
#define CAMELCPP_DEFINEDFUNCTION_H

#include "Function.h"
#include <string>


class DefinedFunction: public Function {
private:
    RuntimeContext* parentContext;
    NodeEnclosedCompoundStatement compoundStatement;

public:
    DefinedFunction(RuntimeContext* &, NodeEnclosedCompoundStatement &);

    Value* invokeFunction(RuntimeEnvironment &, vector<Value *> &) override;

    string toString() override;
};


#endif //CAMELCPP_DEFINEDFUNCTION_H
