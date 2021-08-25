#include "../../header/function/Instance.h"

Instance::Instance(RuntimeEnvironment &environment, RuntimeContext &context) : environment(environment), internalContext(context) {}

Field* Instance::accessField(vector<string> accessedName) {
    return internalContext.accessField(accessedName);
}

Field* Instance::createField(string createdName, Value *createdValue) {
    return internalContext.createField(createdName, createdValue);
}

Value* Instance::performUnaryOperation(Operation::Operation) {
    throw "UnsupportedOperation";
}

Value* Instance::performBinaryOperation(Operation::Operation, Value *) {
    throw "UnsupportedOperation";
}

string Instance::toString() {
    return "Instance";
}
