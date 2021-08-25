#include "../../header/literal/LiteralReturn.h"


LiteralReturn::LiteralReturn(Value* &value) : value(value) {}

Field *LiteralReturn::accessField(vector<string> accessedName) {
    throw "AccessedReturn";
}

Field *LiteralReturn::createField(string createdName, Value* createdValue) {
    throw "AccessedReturn";
}

Value *LiteralReturn::performUnaryOperation(Operation::Operation) {
    throw "AccessedReturn";
}

Value *LiteralReturn::performBinaryOperation(Operation::Operation, Value *) {
    throw "AccessedReturn";
}

string LiteralReturn::toString() {
    throw "AccessedReturn";
}
