#include "../../header/node/NodeConditionalStatement.h"

NodeConditionalStatement::NodeConditionalStatement(Conditional* initialConditional, Conditional* defaultConditional, list<Conditional*> additionalConditionalList)
: initialConditional(initialConditional), defaultConditional(defaultConditional), additionalConditionalList(additionalConditionalList) {}

Value * NodeConditionalStatement::interpret(RuntimeEnvironment &environment, RuntimeContext &context) {
    if (initialConditional->interpret(environment, context))
        return nullptr;

    for (Conditional* additionalConditional : additionalConditionalList) {
        if (additionalConditional->interpret(environment, context))
            return nullptr;
    }

    if (defaultConditional != nullptr)
        defaultConditional->interpret(environment, context);

    return nullptr;
}