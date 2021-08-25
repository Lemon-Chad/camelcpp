#include "../../header/node/NodeVariableDeclarationStatement.h"

NodeVariableDeclarationStatement::NodeVariableDeclarationStatement(vector<string> identifiers, Node* &value)
: identifiers(identifiers), value(value) {}

Value * NodeVariableDeclarationStatement::interpret(RuntimeEnvironment environment, RuntimeContext context) {
    Value* value = this->value->interpret(environment, context);

    if (identifiers.size() == 1) {
        context.createField(identifiers[0], value);
        return value;
    }

    vector<string> identifiers2 = { identifiers.begin() + 1, identifiers.end() };

    Field* field = context.accessField(identifiers2);

    field->getValue()->createField(identifiers[identifiers.size()-1], value);

    return value;
}