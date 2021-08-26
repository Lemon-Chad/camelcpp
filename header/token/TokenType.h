#ifndef CAMELCPP_TOKENTYPE_H
#define CAMELCPP_TOKENTYPE_H


namespace TokenType {
    enum TokenType {
        DEFINITION,
        END_OF_FILE,
        IDENTIFIER,
        QUALIFIER,
        NUMBER,
        STRING,
        OPERATOR_ADD,
        OPERATOR_SUB,
        OPERATOR_MUL,
        OPERATOR_DIV,
        OPERATOR_MORE_THAN,
        OPERATOR_LESS_THAN,
        SEPARATOR,
        L_PAREN,
        R_PAREN,
        PARAMETER,
        OPERATOR_ADD_EQUAL,
        OPERATOR_SUB_EQUAL,
        OPERATOR_MUL_EQUAL,
        OPERATOR_DIV_EQUAL,
        OPERATOR_MORE_EQUAL,
        OPERATOR_LESS_EQUAL,
        OPERATOR_EQUAL,
        OPERATOR_NOT_EQUAL,
        BOOLEAN,
        LOGICAL_AND,
        LOGICAL_OR,
        COMMENT,
        L_BLOCK_BRACKET,
        R_BLOCK_BRACKET,
        OPERATOR_NOT,
        CONDITION,
        THEN,
        LOOP,
        WHITESPACE,
        UNKNOWN,
        STATIC,
        OR,
        FORMAT_STRING,
        L_FORMAT_EXPRESSION,
        R_FORMAT_EXPRESSION,
        REFERENCE
    };
}


#endif //CAMELCPP_TOKENTYPE_H
