#include "../../header/node/NodeLoopStatement.h"
#include "../Helper.cpp"

NodeLoopStatement::NodeLoopStatement(Node* &expression, NodeEnclosedCompoundStatement compoundStatement)
: expression(expression), compoundStatement(compoundStatement) {}

Value * NodeLoopStatement::interpret(RuntimeEnvironment environment, RuntimeContext context) {
    while (true) {
        Value* value = expression->interpret(environment, context);

        if (Helper::asBoolean(value))
            compoundStatement.getEnclosedStatement()->interpret(environment, context);
        else break;
    }
    return nullptr;
}