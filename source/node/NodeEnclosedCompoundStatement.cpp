#include "../../header/node/NodeEnclosedCompoundStatement.h"


NodeEnclosedCompoundStatement::NodeEnclosedCompoundStatement(NodeCompoundStatement* enclosedStatement) : enclosedStatement(enclosedStatement) {}

Value * NodeEnclosedCompoundStatement::interpret(RuntimeEnvironment environment, RuntimeContext context) {
    return enclosedStatement->interpret(environment, context);
}