#include "../../header/literal/LiteralDecimal.h"

using namespace std;


LiteralDecimal::LiteralDecimal(float value) : value(value) {}

Value* LiteralDecimal::performUnaryOperation(Operation::Operation operation) {
    switch (operation) {
        case Operation::ADDITION: return new LiteralDecimal(+value);
        case Operation::SUBTRACTION: return new LiteralDecimal(-value);
        default: throw "UnsupportedOperation";
    }
}

Value *LiteralDecimal::performBinaryOperation(Operation::Operation operation, Value* other) {
    if (dynamic_cast<LiteralDecimal*>(other))
        return Helper::performDecimalOperation(operation, value, dynamic_cast<LiteralDecimal*>(other)->getValue());

    if (dynamic_cast<LiteralInteger*>(other))
        return Helper::performDecimalOperation(operation, value, dynamic_cast<LiteralInteger*>(other)->getValue());

    throw "UnsupportedOperation";
}

string LiteralDecimal::toString() {
    ostringstream stream;
    stream << fixed << setprecision(2) << value;
    return stream.str();
}