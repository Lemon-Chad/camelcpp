#ifndef CAMELCPP_NODEDECIMAL_H
#define CAMELCPP_NODEDECIMAL_H

#include "NodeNumber.h"
#include <string>


class NodeDecimal: public NodeNumber {
private:
    float value;

public:
    static NodeDecimal* parseDecimal(string);

    NodeDecimal(float);

    Value * interpret(RuntimeEnvironment &, RuntimeContext* &);

    float getValue() { return value; }
};


#endif //CAMELCPP_NODEDECIMAL_H
