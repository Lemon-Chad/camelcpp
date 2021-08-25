#include "../../header/node/NodeString.h"


NodeString::NodeString(string value) : value(value) {}

Value * NodeString::interpret(RuntimeEnvironment &environment, RuntimeContext &context) {
    return new LiteralString(value);
}

NodeString *NodeString::parseString(string possibleString) {
    return new NodeString(possibleString);
}
