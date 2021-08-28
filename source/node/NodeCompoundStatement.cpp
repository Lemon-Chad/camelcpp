#include "../../header/node/NodeCompoundStatement.h"
#include "../../header/literal/LiteralReturn.h"
#include <list>

NodeCompoundStatement::NodeCompoundStatement(const list<NodeStatement*> &statementList) : statementList(statementList) {}

Value * NodeCompoundStatement::interpret(RuntimeEnvironment &environment, RuntimeContext* &context) {
    for (NodeStatement* statement : statementList) {
        Value* statementValue = statement->interpret(environment, context);

        if (dynamic_cast<LiteralReturn*>(statementValue)) {
            return dynamic_cast<LiteralReturn *>(statementValue)->getValue();
        }
    }

    return nullptr;
}