#ifndef CAMELCPP_HELPER_H
#define CAMELCPP_HELPER_H

#include "../header/literal/LiteralInteger.h"
#include "../header/literal/LiteralBoolean.h"
#include "../header/literal/LiteralDecimal.h"
#include "../header/literal/LiteralString.h"

namespace Helper {

    static string tokenTypeName(TokenType::TokenType tokenType) {
        switch (tokenType) {
            case TokenType::DEFINITION:
                return "DEFINITION";
            case TokenType::END_OF_FILE:
                return "END_OF_FILE";
            case TokenType::IDENTIFIER:
                return "IDENTIFIER";
            case TokenType::QUALIFIER:
                return "QUALIFIER";
            case TokenType::NUMBER:
                return "NUMBER";
            case TokenType::STRING:
                return "STRING";
            case TokenType::OPERATOR_ADD:
                return "OPERATOR_ADD";
            case TokenType::OPERATOR_SUB:
                return "OPERATOR_SUB";
            case TokenType::OPERATOR_MUL:
                return "OPERATOR_MUL";
            case TokenType::OPERATOR_DIV:
                return "OPERATOR_DIV";
            case TokenType::OPERATOR_MORE_THAN:
                return "OPERATOR_MORE_THAN";
            case TokenType::OPERATOR_LESS_THAN:
                return "OPERATOR_LESS_THAN";
            case TokenType::SEPARATOR:
                return "SEPARATOR";
            case TokenType::L_PAREN:
                return "L_PAREN";
            case TokenType::R_PAREN:
                return "R_PAREN";
            case TokenType::PARAMETER:
                return "PARAMETER";
            case TokenType::OPERATOR_ADD_EQUAL:
                return "OPERATOR_ADD_EQUAL";
            case TokenType::OPERATOR_SUB_EQUAL:
                return "OPERATOR_SUB_EQUAL";
            case TokenType::OPERATOR_MUL_EQUAL:
                return "OPERATOR_MUL_EQUAL";
            case TokenType::OPERATOR_DIV_EQUAL:
                return "OPERATOR_DIV_EQUAL";
            case TokenType::OPERATOR_MORE_EQUAL:
                return "OPERATOR_MORE_EQUAL";
            case TokenType::OPERATOR_LESS_EQUAL:
                return "OPERATOR_LESS_EQUAL";
            case TokenType::OPERATOR_EQUAL:
                return "OPERATOR_EQUAL";
            case TokenType::OPERATOR_NOT_EQUAL:
                return "OPERATOR_NOT_EQUAL";
            case TokenType::BOOLEAN:
                return "BOOLEAN";
            case TokenType::LOGICAL_AND:
                return "LOGICAL_AND";
            case TokenType::LOGICAL_OR:
                return "LOGICAL_OR";
            case TokenType::COMMENT:
                return "COMMENT";
            case TokenType::L_BLOCK_BRACKET:
                return "L_BLOCK_BRACKET";
            case TokenType::R_BLOCK_BRACKET:
                return "R_BLOCK_BRACKET";
            case TokenType::OPERATOR_NOT:
                return "OPERATOR_NOT";
            case TokenType::CONDITION:
                return "CONDITION";
            case TokenType::THEN:
                return "THEN";
            case TokenType::LOOP:
                return "LOOP";
            case TokenType::WHITESPACE:
                return "WHITESPACE";
            case TokenType::STATIC:
                return "STATIC";
            case TokenType::OR:
                return "OR";
            case TokenType::FORMAT_STRING:
                return "FORMAT_STRING";
            case TokenType::L_FORMAT_EXPRESSION:
                return "L_FORMAT_EXPRESSION";
            case TokenType::R_FORMAT_EXPRESSION:
                return "R_FORMAT_EXPRESSION";
            case TokenType::REFERENCE:
                return "REFERENCE";
            default:
                return "UNKNOWN";
        };
    }

    static Value* performIntegerOperation(Operation::Operation operation, int operandL, int operandR) {
        switch (operation) {
            case Operation::ADDITION: return new LiteralInteger(operandL + operandR);
            case Operation::SUBTRACTION: return new LiteralInteger(operandL - operandR);
            case Operation::MULTIPLICATION: return new LiteralInteger(operandL * operandR);
            case Operation::DIVISION: return new LiteralInteger(operandL / operandR);

            case Operation::EQUAL: return new LiteralBoolean(operandL == operandR);
            case Operation::NOT_EQUAL: return new LiteralBoolean(operandL != operandR);

            case Operation::MORE_THAN: return new LiteralBoolean(operandL > operandR);
            case Operation::LESS_THAN: return new LiteralBoolean(operandL < operandR);

            case Operation::MORE_EQUAL: return new LiteralBoolean(operandL >= operandR);
            case Operation::LESS_EQUAL: return new LiteralBoolean(operandL <= operandR);

            default: throw "UnsupportedOperation";
        }
    }

    static Value* performDecimalOperation(Operation::Operation operation, float operandL, float operandR) {
        switch (operation) {
            case Operation::ADDITION: return new LiteralDecimal(operandL + operandR);
            case Operation::SUBTRACTION: return new LiteralDecimal(operandL - operandR);
            case Operation::MULTIPLICATION: return new LiteralDecimal(operandL * operandR);
            case Operation::DIVISION: return new LiteralDecimal(operandL / operandR);

            case Operation::EQUAL: return new LiteralBoolean(operandL == operandR);
            case Operation::NOT_EQUAL: return new LiteralBoolean(operandL != operandR);

            case Operation::MORE_THAN: return new LiteralBoolean(operandL > operandR);
            case Operation::LESS_THAN: return new LiteralBoolean(operandL < operandR);

            case Operation::MORE_EQUAL: return new LiteralBoolean(operandL >= operandR);
            case Operation::LESS_EQUAL: return new LiteralBoolean(operandL <= operandR);

            default: throw "UnsupportedOperation";
        }
    }

    static Value* performStringOperation(Operation::Operation operation, string operandL, string operandR) {
        switch (operation) {
            case Operation::ADDITION: return new LiteralString(operandL + operandR);

            case Operation::EQUAL: return new LiteralBoolean(operandL == operandR);
            case Operation::NOT_EQUAL: return new LiteralBoolean(operandL != operandR);

            default: throw "UnsupportedOperation";
        }
    }

    static Value* performBooleanOperation(Operation::Operation operation, bool operandL, bool operandR) {
        switch (operation) {
            case Operation::EQUAL: return new LiteralBoolean(operandL == operandR);
            case Operation::NOT_EQUAL: return new LiteralBoolean(operandL != operandR);

            case Operation::LOGICAL_AND: return new LiteralBoolean(operandL && operandR);
            case Operation::LOGICAL_OR: return new LiteralBoolean(operandL || operandR);

            default: throw "UnsupportedOperation";
        }
    }

    static bool asBoolean(Value* &value) {
        return dynamic_cast<LiteralBoolean*>(value) && dynamic_cast<LiteralBoolean*>(value)->getValue();
    }
};

#endif //CAMELCPP_HELPER_H