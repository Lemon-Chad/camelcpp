#include "../../header/node/NodeStaticDeclarationStatement.h"
#include "../../header/native/Instance.h"


NodeStaticDeclarationStatement::NodeStaticDeclarationStatement(string identifier, NodeEnclosedCompoundStatement* compoundStatement)
: identifier(identifier), compoundStatement(compoundStatement) {}

Value * NodeStaticDeclarationStatement::interpret(RuntimeEnvironment &environment, RuntimeContext* &context) {
    RuntimeContext* internalContext = new RuntimeContext(context);

    compoundStatement->interpret(environment, internalContext);

    Instance* instance = new Instance(environment, internalContext);

    context->createField(identifier, instance);

    return instance;
}