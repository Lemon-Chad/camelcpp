#ifndef CAMELCPP_RUNTIMECONTEXT_H
#define CAMELCPP_RUNTIMECONTEXT_H


#include "Field.h"

class RuntimeContext {
private:
    vector<Field*> fieldList;

    vector<Value*> argumentList;

public:
    RuntimeContext(RuntimeContext* &, vector<Value*> &);
    RuntimeContext(RuntimeContext* &);

    Field* accessField(vector<string> &);
    Field* createField(string, Value*);

    Field* getField(string);
    Value* getArgument();

    bool hasArgument();

    RuntimeContext* parentContext;
};


#endif //CAMELCPP_RUNTIMECONTEXT_H
