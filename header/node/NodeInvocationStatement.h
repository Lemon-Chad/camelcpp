#ifndef CAMELCPP_NODEINVOCATIONSTATEMENT_H
#define CAMELCPP_NODEINVOCATIONSTATEMENT_H

#include "NodeStatement.h"
#include "NodeVariable.h"
#include "NodeArgumentList.h"

using namespace std;


class NodeInvocationStatement: public NodeStatement {
private:
    NodeVariable variable;
    NodeArgumentList argumentList;

public:
    NodeInvocationStatement(NodeVariable, NodeArgumentList);

    Value * interpret(RuntimeEnvironment &, RuntimeContext &);

    NodeVariable getVariable() { return variable; }
    NodeArgumentList getArgumentList() { return argumentList; }
};


#endif //CAMELCPP_NODEINVOCATIONSTATEMENT_H
