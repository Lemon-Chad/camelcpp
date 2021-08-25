#ifndef CAMELCPP_INTERPRETER_H
#define CAMELCPP_INTERPRETER_H

#include "../node/NodeCompoundStatement.h"


class Interpreter {
public:
    static void interpret(NodeCompoundStatement &);
};


#endif //CAMELCPP_INTERPRETER_H
