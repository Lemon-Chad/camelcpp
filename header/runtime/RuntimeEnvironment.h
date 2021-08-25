#ifndef CAMELCPP_RUNTIMEENVIRONMENT_H
#define CAMELCPP_RUNTIMEENVIRONMENT_H

#include <iostream>
#include <string>
#include "RuntimeContext.h"

using namespace std;


class RuntimeEnvironment {
private:
    RuntimeContext* context;

public:
    RuntimeEnvironment(RuntimeContext*);

    RuntimeContext* getContext() { return context; }
};


#endif //CAMELCPP_RUNTIMEENVIRONMENT_H
