//
// Created by Myles Harris on 8/24/21.
//

#ifndef CAMELCPP_NODECONDITIONALSTATEMENT_H
#define CAMELCPP_NODECONDITIONALSTATEMENT_H

#include "Conditional.h"
#include "NodeStatement.h"
#include "NodeEnclosedCompoundStatement.h"

using namespace std;

class NodeConditionalStatement: public NodeStatement {
private:
    Conditional* initialConditional;
    Conditional* defaultConditional;
    list<Conditional*> additionalConditionalList;

public:
    NodeConditionalStatement(Conditional*, Conditional*, list<Conditional*>);

    Value * interpret(RuntimeEnvironment, RuntimeContext);

    Conditional* getInitialConditional() { return initialConditional; }
    Conditional* getDefaultConditional() { return defaultConditional; }
    list<Conditional*> getAdditionalConditionalList() { return additionalConditionalList; }
};

#endif //CAMELCPP_NODECONDITIONALSTATEMENT_H
