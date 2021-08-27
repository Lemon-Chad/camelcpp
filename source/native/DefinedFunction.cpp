#include "../../header/native/DefinedFunction.h"

DefinedFunction::DefinedFunction(RuntimeContext* &context, NodeEnclosedCompoundStatement &compoundStatement)
: parentContext(context), compoundStatement(compoundStatement) {}

Value* DefinedFunction::invokeFunction(RuntimeEnvironment &environment, vector<Value *> &arguments) {
    RuntimeContext* invocationContext = new RuntimeContext(parentContext, arguments);

    return compoundStatement.interpret(environment, invocationContext);
}

string DefinedFunction::toString() {
    return "DefinedFunction";
}
