//
// Created by Myles Harris on 8/23/21.
//

#ifndef CAMELCPP_RUNTIMECONTEXT_H
#define CAMELCPP_RUNTIMECONTEXT_H


#include "Field.h"

class RuntimeContext {
private:
    RuntimeContext* parentContext;
    vector<Field*> fieldList;

    vector<Value*> argumentList;

public:
    RuntimeContext(RuntimeContext* &, vector<Value*> &);
    RuntimeContext(RuntimeContext* &);

    Field* accessField(vector<string> &);
    Field* createField(string, Value* &);

    Field* getField(string);
    Value* getArgument();

    bool hasArgument();
};


#endif //CAMELCPP_RUNTIMECONTEXT_H
