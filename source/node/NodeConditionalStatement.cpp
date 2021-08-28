#include "../../header/node/NodeConditionalStatement.h"
#include <list>

NodeConditionalStatement::NodeConditionalStatement(Conditional* initialConditional, Conditional* defaultConditional, list<Conditional*> additionalConditionalList)
: initialConditional(initialConditional), defaultConditional(defaultConditional), additionalConditionalList(additionalConditionalList) {}

Value* handleReturn(Value* value) {
    if (value == nullptr) return value;
    return new LiteralReturn(value);
}

Value * NodeConditionalStatement::interpret(RuntimeEnvironment &environment, RuntimeContext* &context) {
    ConditionalResult conditionalResult = initialConditional->interpret(environment, context);

    if (conditionalResult.getSuccess()) 
        return handleReturn(conditionalResult.getResult());

    for (Conditional* additionalConditional : additionalConditionalList) {
        conditionalResult = additionalConditional->interpret(environment, context);
        if (conditionalResult.getSuccess()) return handleReturn(conditionalResult.getResult());
    }

    if (defaultConditional != nullptr) {
        conditionalResult = defaultConditional->interpret(environment, context);
        if (conditionalResult.getSuccess()) return handleReturn(conditionalResult.getResult());
    }

    return nullptr;
}