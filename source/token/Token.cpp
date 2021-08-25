#include <sstream>
#include "../../header/token/Token.h"

bool Token::isWhitespace()
{
    return type == TokenType::WHITESPACE;
}

Token::Token(TokenType::TokenType type, const string &content)
{
    this->type = type;

    this->content = content;
}