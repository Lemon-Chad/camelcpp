#include "../../header/node/NodeStaticDeclarationStatement.h"
#include "../../header/function/Instance.h"


NodeStaticDeclarationStatement::NodeStaticDeclarationStatement(string identifier, NodeEnclosedCompoundStatement* compoundStatement)
: identifier(identifier), compoundStatement(compoundStatement) {}

Value * NodeStaticDeclarationStatement::interpret(RuntimeEnvironment &environment, RuntimeContext &context) {
    RuntimeContext internalContext = RuntimeContext(context);

    compoundStatement->interpret(environment, internalContext);

    Instance* instance = new Instance(environment, internalContext);

    context.createField(identifier, instance);

    return instance;
}