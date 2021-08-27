#include "../../header/node/NodeExpression.h"


NodeExpression::NodeExpression(Node* &term, list<Operand> &operandList) : term(term), operandList(operandList) {}

Value * NodeExpression::interpret(RuntimeEnvironment &environment, RuntimeContext* &context) {
    Value* expressionValue = term->interpret(environment, context);

    for (Operand operand : operandList) {
        Value* operandValue = operand.getTerm()->interpret(environment, context);
        expressionValue = expressionValue->performBinaryOperation(operand.getOperation(), operandValue);
    }
    return expressionValue;
}