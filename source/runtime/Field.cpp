#include "../../header/runtime/Field.h"

Field::Field(string name, Value * &value) : name(name), value(value) {}

void Field::setValue(Value* value) {
    delete this->value;
    this->value = value;
}