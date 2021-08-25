#include "../../header/literal/LiteralString.h"


LiteralString::LiteralString(string value) : value(value) {}

Value *LiteralString::performUnaryOperation(Operation::Operation) {
    throw "UnsupportedOperation";
}

Value *LiteralString::performBinaryOperation(Operation::Operation operation, Value* other) {
    if (dynamic_cast<LiteralString*>(other))
        return Helper::performStringOperation(operation, value, dynamic_cast<LiteralString*>(other)->getValue());

    throw "UnsupportedOperation";
}

string LiteralString::toString() {
    return value;
}
