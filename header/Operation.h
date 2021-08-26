//
// Created by Myles Harris on 8/24/21.
//

#ifndef CAMELCPP_OPERATION_H
#define CAMELCPP_OPERATION_H


namespace Operation {
    enum Operation {
        ADDITION,
        SUBTRACTION,
        MULTIPLICATION,
        DIVISION,
        EQUAL,
        NOT_EQUAL,
        MORE_THAN,
        LESS_THAN,
        MORE_EQUAL,
        LESS_EQUAL,
        LOGICAL_AND,
        LOGICAL_OR,
        UNARY_NOT,
        REFERENCE,
        UNKNOWN
    };
}

#endif //CAMELCPP_OPERATION_H