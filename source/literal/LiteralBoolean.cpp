#include "../../header/literal/LiteralBoolean.h"

using namespace std;


LiteralBoolean::LiteralBoolean(bool value) : value(value) {}

Value *LiteralBoolean::performUnaryOperation(Operation::Operation operation) {
    if (operation == Operation::UNARY_NOT)
    {
        return new LiteralBoolean(!value);
    }
    throw "UnsupportedOperation";
}

Value *LiteralBoolean::performBinaryOperation(Operation::Operation operation, Value* other) {
    if (dynamic_cast<LiteralBoolean*>(other))
        return Helper::performBooleanOperation(operation, value, dynamic_cast<LiteralBoolean*>(other)->getValue());

    throw "UnsupportedOperation";
}

string LiteralBoolean::toString() {
    return to_string(value);
}
