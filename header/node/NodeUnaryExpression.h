#ifndef CAMELCPP_NODEUNARYEXPRESSION_H
#define CAMELCPP_NODEUNARYEXPRESSION_H

#include "Node.h"

using namespace std;


class NodeUnaryExpression: public Node {
private:
    Operation::Operation operation;
    Node* term;

public:
    NodeUnaryExpression(Operation::Operation, Node* &);

    Value * interpret(RuntimeEnvironment, RuntimeContext);

    Operation::Operation getOperation() { return operation; }
    Node* getTerm() { return term; }
};


#endif //CAMELCPP_NODEUNARYEXPRESSION_H
