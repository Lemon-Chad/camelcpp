#ifndef CAMELCPP_NODE_H
#define CAMELCPP_NODE_H


#include "../runtime/RuntimeEnvironment.h"
#include "../runtime/RuntimeContext.h"
#include "../value/Value.h"

class Node {

public:
    virtual Value * interpret(RuntimeEnvironment, RuntimeContext) = 0;
};


#endif //CAMELCPP_NODE_H
