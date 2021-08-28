#ifndef CAMELCPP_FIELD_H
#define CAMELCPP_FIELD_H

#include <string>
#include <vector>
#include "../value/Value.h"

using namespace std;


class Value;

class Field {
private:
    string name;
    Value* value;

public:
    string getName() { return name; }
    Value* getValue() { return value; }
    void setValue(Value* value);

    Field(string, Value* &);
};


#endif //CAMELCPP_FIELD_H
