#include "../../header/literal/LiteralInteger.h"

using namespace std;


LiteralInteger::LiteralInteger(int value) : value(value) {}

Value* LiteralInteger::performUnaryOperation(Operation::Operation operation) {
    switch (operation) {
        case Operation::ADDITION: return new LiteralInteger(+value);
        case Operation::SUBTRACTION: return new LiteralInteger(-value);
        default: throw "UnsupportedOperation";
    }
}

Value *LiteralInteger::performBinaryOperation(Operation::Operation operation, Value* other) {
    if (dynamic_cast<LiteralDecimal*>(other))
        return Helper::performDecimalOperation(operation, value, dynamic_cast<LiteralInteger*>(other)->getValue());

    if (dynamic_cast<LiteralInteger*>(other))
        return Helper::performIntegerOperation(operation, value, dynamic_cast<LiteralInteger*>(other)->getValue());

    throw "UnsupportedOperation";
}

string LiteralInteger::toString() {
    return to_string(value);
}
