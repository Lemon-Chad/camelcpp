#include "../../header/node/NodeFunctionDeclarationStatement.h"
#include "../../header/native/DefinedFunction.h"


NodeFunctionDeclarationStatement::NodeFunctionDeclarationStatement(NodeVariable variable, NodeEnclosedCompoundStatement compoundStatement)
: variable(variable), compoundStatement(compoundStatement) {}

Value * NodeFunctionDeclarationStatement::interpret(RuntimeEnvironment &environment, RuntimeContext &context) {
    DefinedFunction* function = new DefinedFunction(context, compoundStatement);

    vector<string> identifiers = variable.getIdentifiers();

    if (identifiers.size() == 1) {
        context.createField(identifiers[0], function);

        return function;
    }

    vector<string> identifiers2 = {identifiers.begin(), identifiers.end()-1};

    Field* field = context.accessField(identifiers2);

    field->getValue()->createField(identifiers[identifiers.size()-1], function);

    return function;
}