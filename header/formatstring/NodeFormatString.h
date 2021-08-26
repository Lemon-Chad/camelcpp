#ifndef CAMELCPP_NODEFORMATSTRING_H
#define CAMELCPP_NODEFORMATSTRING_H

#include "../node/Node.h"
#include "FormatStringComponent.h"


class NodeFormatString: public Node {
private:
    vector<FormatStringComponent*> componentList;

public:
    NodeFormatString(vector<FormatStringComponent*> &);

    Value * interpret(RuntimeEnvironment &, RuntimeContext &);
};


#endif //CAMELCPP_NODEFORMATSTRING_H
