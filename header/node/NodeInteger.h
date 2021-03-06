#ifndef CAMELCPP_NODEINTEGER_H
#define CAMELCPP_NODEINTEGER_H

#include "NodeNumber.h"
#include <string>


class NodeInteger: public NodeNumber {
private:
    int value;

public:
    static NodeInteger* parseInteger(string);

    NodeInteger(int);

    Value * interpret(RuntimeEnvironment &, RuntimeContext* &);

    int getValue() { return value; }
};


#endif //CAMELCPP_NODEINTEGER_H
