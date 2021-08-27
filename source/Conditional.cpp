#include "../header/node/Conditional.h"
#include "../header/literal/LiteralBoolean.h"
#include "Helper.cpp"

Conditional::Conditional(Node* &expression, NodeEnclosedCompoundStatement* &compoundStatement): expression(expression), compoundStatement(compoundStatement) {}

bool Conditional::interpret(RuntimeEnvironment &environment, RuntimeContext* &context) {
    if (expression == nullptr) {
        compoundStatement->getEnclosedStatement()->interpret(environment, context);
        return true;
    }

    Value* expressionResult = expression->interpret(environment, context);

    if (Helper::asBoolean(expressionResult)) {
        compoundStatement->getEnclosedStatement()->interpret(environment, context);
        return true;
    }
    return false;
}