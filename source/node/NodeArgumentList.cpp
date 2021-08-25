#include "../../header/node/NodeArgumentList.h"

NodeArgumentList::NodeArgumentList(const vector<Node*> &argumentList) : argumentList(argumentList) {}

Value * NodeArgumentList::interpret(RuntimeEnvironment &environment, RuntimeContext &context) {
    throw "CannotInterpret";
}