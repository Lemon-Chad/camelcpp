#ifndef CAMELCPP_NODEVARIABLE_H
#define CAMELCPP_NODEVARIABLE_H

#include <vector>
#include "Node.h"
#include <string>

using namespace std;


class NodeVariable: public Node {
private:
    vector<string> identifiers;

public:
    NodeVariable(vector<string> identifiers);

    Value * interpret(RuntimeEnvironment &, RuntimeContext* &);

    vector<string> getIdentifiers() { return identifiers; }
};


#endif //CAMELCPP_NODEVARIABLE_H
