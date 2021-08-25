#ifndef CAMELCPP_NODESTRING_H
#define CAMELCPP_NODESTRING_H

#include "Node.h"


class NodeString: public Node {
private:
    string value;

public:
    static NodeString* parseString(string);

    NodeString(string);

    Value * interpret(RuntimeEnvironment, RuntimeContext);

    string getValue() { return value; }
};


#endif //CAMELCPP_NODESTRING_H
