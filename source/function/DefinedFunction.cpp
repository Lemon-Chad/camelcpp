#include "../../header/function/DefinedFunction.h"

DefinedFunction::DefinedFunction(RuntimeContext &context, NodeEnclosedCompoundStatement &compoundStatement)
: parentContext(context), compoundStatement(compoundStatement) {}

Value* DefinedFunction::invokeFunction(RuntimeEnvironment &environment, vector<Value *> &arguments) {
    RuntimeContext* parentContext1 = &parentContext;
    RuntimeContext invocationContext = RuntimeContext(parentContext1, arguments);

    return compoundStatement.interpret(environment, invocationContext);
}

string DefinedFunction::toString() {
    return "DefinedFunction";
}
