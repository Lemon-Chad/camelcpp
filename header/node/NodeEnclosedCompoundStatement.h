#ifndef CAMELCPP_NODEENCLOSEDCOMPOUNDSTATEMENT_H
#define CAMELCPP_NODEENCLOSEDCOMPOUNDSTATEMENT_H

#include "NodeStatement.h"
#include "NodeCompoundStatement.h"

class NodeEnclosedCompoundStatement: public NodeStatement {
private:
    NodeCompoundStatement* enclosedStatement;

public:
    NodeEnclosedCompoundStatement(NodeCompoundStatement*);

    Value * interpret(RuntimeEnvironment &, RuntimeContext* &);

    NodeCompoundStatement* getEnclosedStatement() { return enclosedStatement; }
};


#endif //CAMELCPP_NODEENCLOSEDCOMPOUNDSTATEMENT_H
