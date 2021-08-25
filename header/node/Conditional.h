//
// Created by Myles Harris on 8/24/21.
//

#ifndef CAMELCPP_CONDITIONAL_H
#define CAMELCPP_CONDITIONAL_H

#include "Node.h"
#include "NodeEnclosedCompoundStatement.h"


class Conditional {
private:
    Node *expression;
    NodeEnclosedCompoundStatement *compoundStatement;

public:
    Conditional(Node* &, NodeEnclosedCompoundStatement* &);

    bool interpret(RuntimeEnvironment &, RuntimeContext &);

    const Node* getExpression() { return expression; };
    const NodeEnclosedCompoundStatement* getCompoundStatement() { return compoundStatement; }
};


#endif //CAMELCPP_CONDITIONAL_H
