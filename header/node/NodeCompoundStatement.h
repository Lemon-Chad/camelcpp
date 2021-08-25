#ifndef CAMELCPP_NODECOMPOUNDSTATEMENT_H
#define CAMELCPP_NODECOMPOUNDSTATEMENT_H

#include "NodeStatement.h"

using namespace std;


class NodeCompoundStatement: public NodeStatement {
private:
    list<NodeStatement*> statementList;

public:
    NodeCompoundStatement(const list<NodeStatement*> & statementList);

    Value * interpret(RuntimeEnvironment, RuntimeContext);

    list<NodeStatement*> getStatementList() { return statementList; }
};


#endif //CAMELCPP_NODECOMPOUNDSTATEMENT_H
