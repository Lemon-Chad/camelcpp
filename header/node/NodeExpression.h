#ifndef CAMELCPP_NODEEXPRESSION_H
#define CAMELCPP_NODEEXPRESSION_H

#include "Node.h"
#include "../Operand.h"

using namespace std;


class NodeExpression: public Node {
private:
    Node* term;

    list<Operand> operandList;

public:
    NodeExpression(Node* &, list<Operand> &);
    Value * interpret(RuntimeEnvironment &, RuntimeContext &);
};


#endif //CAMELCPP_NODEEXPRESSION_H
