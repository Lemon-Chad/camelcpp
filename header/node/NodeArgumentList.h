//
// Created by Myles Harris on 8/23/21.
//

#ifndef CAMELCPP_NODEARGUMENTLIST_H
#define CAMELCPP_NODEARGUMENTLIST_H

#include "Node.h"

using namespace std;


class NodeArgumentList : public Node {
private:
    vector<Node*> argumentList;

public:
    NodeArgumentList(const vector<Node*> &);

    Value * interpret(RuntimeEnvironment, RuntimeContext);

    vector<Node*> getArgumentList() { return argumentList; }
};


#endif //CAMELCPP_NODEARGUMENTLIST_H
