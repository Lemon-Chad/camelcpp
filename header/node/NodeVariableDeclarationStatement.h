#ifndef CAMELCPP_NODEVARIABLEDECLARATIONSTATEMENT_H
#define CAMELCPP_NODEVARIABLEDECLARATIONSTATEMENT_H

#include "NodeStatement.h"


class NodeVariableDeclarationStatement: public NodeStatement {
private:
    vector<string> identifiers;
    Node* value;

public:
    NodeVariableDeclarationStatement(vector<string>, Node* &);

    Value * interpret(RuntimeEnvironment &, RuntimeContext &);

    vector<string> getIdentifiers() { return identifiers; }
    Node* getValue() { return value; }
};


#endif //CAMELCPP_NODEVARIABLEDECLARATIONSTATEMENT_H
