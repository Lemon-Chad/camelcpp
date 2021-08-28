#include "../header/node/Conditional.h"
#include "../header/literal/LiteralBoolean.h"
#include "Helper.cpp"

ConditionalResult::ConditionalResult(Value* result, bool success): result(result), success(success) {}

Conditional::Conditional(Node* &expression, NodeEnclosedCompoundStatement* &compoundStatement): expression(expression), compoundStatement(compoundStatement) {}

ConditionalResult Conditional::interpret(RuntimeEnvironment &environment, RuntimeContext* &context) {
    if (expression == nullptr) 
        return ConditionalResult(compoundStatement->getEnclosedStatement()->interpret(environment, context), true);

    Value* expressionResult = expression->interpret(environment, context);
 
    if (Helper::asBoolean(expressionResult)) 
        return ConditionalResult(compoundStatement->getEnclosedStatement()->interpret(environment, context), true);
    
    return ConditionalResult(nullptr, false);
}