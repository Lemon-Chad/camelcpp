#ifndef CAMELCPP_NODEFUNCTIONDECLARATIONSTATEMENT_H
#define CAMELCPP_NODEFUNCTIONDECLARATIONSTATEMENT_H

#include "NodeStatement.h"
#include "NodeVariable.h"
#include "NodeEnclosedCompoundStatement.h"

using namespace std;


class NodeFunctionDeclarationStatement: public NodeStatement {
private:
    NodeVariable variable;
    NodeEnclosedCompoundStatement compoundStatement;

public:
    NodeFunctionDeclarationStatement(NodeVariable, NodeEnclosedCompoundStatement);

    Value * interpret(RuntimeEnvironment, RuntimeContext);

    NodeVariable getVariable() { return variable; }
    NodeEnclosedCompoundStatement getCompoundStatement() { return compoundStatement; }
};


#endif //CAMELCPP_NODEFUNCTIONDECLARATIONSTATEMENT_H
