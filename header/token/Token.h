#ifndef CAMELCPP_TOKEN_H
#define CAMELCPP_TOKEN_H

#include <iostream>
#include "TokenType.h"

using namespace std;

class Token {

private:
    TokenType::TokenType type;

    string content;

public:
    Token(TokenType::TokenType type, const string &content);

    bool isWhitespace();

    TokenType::TokenType getType() const { return type; }
    string getContent() const { return content; }
};


#endif //CAMELCPP_TOKEN_H
