#ifndef CAMELCPP_CONDITIONAL_H
#define CAMELCPP_CONDITIONAL_H

#include "Node.h"
#include "NodeEnclosedCompoundStatement.h"


class ConditionalResult {
private:
    Value *result;
    bool success;

public:
    ConditionalResult(Value*, bool);

    Value* getResult() { return result; }
    bool getSuccess() { return success; }
};

class Conditional {
private:
    Node *expression;
    NodeEnclosedCompoundStatement *compoundStatement;

public:
    Conditional(Node* &, NodeEnclosedCompoundStatement* &);

    ConditionalResult interpret(RuntimeEnvironment &, RuntimeContext* &);

    const Node* getExpression() { return expression; };
    const NodeEnclosedCompoundStatement* getCompoundStatement() { return compoundStatement; }
};

#endif //CAMELCPP_CONDITIONAL_H
