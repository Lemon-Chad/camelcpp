#include "../../header/node/NodeInteger.h"
#include "../../header/literal/LiteralInteger.h"


NodeInteger::NodeInteger(int value) : value(value) {}

Value * NodeInteger::interpret(RuntimeEnvironment &environment, RuntimeContext &context) {
    return new LiteralInteger(value);
}

NodeInteger* NodeInteger::parseInteger(string possibleInteger) {
    return new NodeInteger(stoi(possibleInteger));
}
