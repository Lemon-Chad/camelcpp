//
// Created by Myles Harris on 8/24/21.
//

#ifndef CAMELCPP_NODESTATEMENT_H
#define CAMELCPP_NODESTATEMENT_H

#include "Node.h"


class NodeStatement: public Node {
public:
    virtual Value * interpret(RuntimeEnvironment &, RuntimeContext &) = 0;
};


#endif //CAMELCPP_NODESTATEMENT_H
