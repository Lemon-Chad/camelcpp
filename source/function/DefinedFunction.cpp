#include "../../header/function/DefinedFunction.h"

DefinedFunction::DefinedFunction(RuntimeContext &context, NodeEnclosedCompoundStatement &compoundStatement)
: parentContext(context), compoundStatement(compoundStatement) {}

Value* DefinedFunction::invokeFunction(RuntimeEnvironment &environment, RuntimeContext &context) {
    return compoundStatement.interpret(environment, context);
}

string DefinedFunction::toString() {
    return "DefinedFunction";
}
