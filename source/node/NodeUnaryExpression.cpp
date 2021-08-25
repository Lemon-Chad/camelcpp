#include "../../header/node/NodeUnaryExpression.h"


NodeUnaryExpression::NodeUnaryExpression(Operation::Operation operation, Node* &term)
: operation(operation), term(term) {}

Value * NodeUnaryExpression::interpret(RuntimeEnvironment environment, RuntimeContext context) {
    return term->interpret(environment, context)->performUnaryOperation(operation);
}