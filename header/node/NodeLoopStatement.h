#ifndef CAMELCPP_NODELOOPSTATEMENT_H
#define CAMELCPP_NODELOOPSTATEMENT_H

#include "NodeStatement.h"
#include "NodeEnclosedCompoundStatement.h"


class NodeLoopStatement: public NodeStatement {
private:
    Node* expression;
    NodeEnclosedCompoundStatement compoundStatement;

public:
    NodeLoopStatement(Node* &, NodeEnclosedCompoundStatement);

    Value * interpret(RuntimeEnvironment, RuntimeContext);

    Node* getExpression() { return expression; }
    NodeEnclosedCompoundStatement getCompoundStatement() { return compoundStatement; }
};


#endif //CAMELCPP_NODELOOPSTATEMENT_H
