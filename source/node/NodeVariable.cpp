//
// Created by Myles Harris on 8/24/21.
//

#include "../../header/node/NodeVariable.h"
#include "../../header/function/Instance.h"

NodeVariable::NodeVariable(vector<string> identifiers) : identifiers(identifiers) {}

Value * NodeVariable::interpret(RuntimeEnvironment &environment, RuntimeContext &context) {
    if (identifiers.size() == 1 && identifiers[0] == "self")
        return new Instance(environment, context);

    if (identifiers.size() == 1 && identifiers[0] == "param")
        return context.getArgument();

    Field* field = context.accessField(identifiers);
    if (field != nullptr) return field->getValue();
    return nullptr;
}