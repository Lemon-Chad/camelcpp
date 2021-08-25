#include "../../header/node/NodeBoolean.h"
#include "../../header/literal/LiteralBoolean.h"

NodeBoolean::NodeBoolean(bool value) : value(value) {}

Value * NodeBoolean::interpret(RuntimeEnvironment environment, RuntimeContext context) {
    return new LiteralBoolean(value);
}

NodeBoolean *NodeBoolean::parseBoolean(string possibleBoolean) {
    return new NodeBoolean(possibleBoolean == "true");
}