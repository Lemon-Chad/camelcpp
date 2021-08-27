#include "../../header/node/NodeDecimal.h"


NodeDecimal::NodeDecimal(float value) : value(value) {}

Value * NodeDecimal::interpret(RuntimeEnvironment &environment, RuntimeContext* &context) {
    return new LiteralDecimal(value);
}

NodeDecimal *NodeDecimal::parseDecimal(string possibleDecimal) {
    return new NodeDecimal(stof(possibleDecimal));
}
