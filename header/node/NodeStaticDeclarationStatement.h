#ifndef CAMELCPP_NODESTATICDECLARATIONSTATEMENT_H
#define CAMELCPP_NODESTATICDECLARATIONSTATEMENT_H

#include "NodeStatement.h"
#include "NodeEnclosedCompoundStatement.h"

using namespace std;


class NodeStaticDeclarationStatement: public NodeStatement {
private:
    string identifier;
    NodeEnclosedCompoundStatement* compoundStatement;

public:
    NodeStaticDeclarationStatement(string, NodeEnclosedCompoundStatement*);

    Value * interpret(RuntimeEnvironment &, RuntimeContext* &);

    string getIdentifier() { return identifier; }
    NodeEnclosedCompoundStatement* getCompoundStatement() { return compoundStatement; }
};


#endif //CAMELCPP_NODESTATICDECLARATIONSTATEMENT_H
