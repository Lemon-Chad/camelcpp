#ifndef CAMELCPP_OPERAND_H
#define CAMELCPP_OPERAND_H

#include "Operation.h"


class Operand {
private:
    Operation::Operation operation;
    Node* term;

public:
    Operand(Operation::Operation, Node*);

    Operation::Operation getOperation() { return operation; }
    Node* getTerm() { return term; }
};


#endif //CAMELCPP_OPERAND_H
