#ifndef CAMELCPP_NODENUMBER_H
#define CAMELCPP_NODENUMBER_H

#include "Node.h"


class NodeNumber: public Node {
public:
    virtual Value * interpret(RuntimeEnvironment &, RuntimeContext &) = 0;
};


#endif //CAMELCPP_NODENUMBER_H
