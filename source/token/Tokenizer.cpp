#include <sstream>
#include "../../header/token/Tokenizer.h"
#include "../CharacterReader.cpp"
#include "Token.cpp"

using namespace std;

static TokenType::TokenType fromSingleOperation(char);
static TokenType::TokenType fromDoubleOperation(string);
static TokenType::TokenType fromKeyword(string keyword);

static const string OPERATION_CHARACTERS = "!?>+-*/^<=,(){}|&";

enum Exception {
    UNKNOWN_SYMBOL=-15,
    UNKNOWN_OPERATOR=-16
};

vector<Token> Tokenizer::tokenize(ifstream &inputFileStream)
{
    CharacterReader reader = CharacterReader(inputFileStream);

    vector<Token> tokenList;

    while (reader.peek()) {
        reader.next();

        if (reader.curr() == '#') {
            tokenList.push_back(tokenizeComment(reader));
        }
        else if (isdigit(reader.curr())) {
            tokenList.push_back(tokenizeNumberLiteral(reader, 0));
        }
        else if (reader.curr() == '"') {
            tokenList.push_back(tokenizeStringLiteral(reader));
        }
        else if (reader.curr() == '.') {
            tokenList.push_back(tokenizeQualifier(reader));
        }
        else if (OPERATION_CHARACTERS.find(reader.curr()) != string::npos) {
            tokenList.push_back(tokenizeOperation(reader));
        }
        else if (isalnum(reader.curr()) || reader.curr() == '_') {
            tokenList.push_back(tokenizeIdentifier(reader));
        }
        else if (isspace(reader.curr())) {
            tokenList.push_back(Token(TokenType::WHITESPACE, reader.curr_str()));
        }
        else {
            throw Exception::UNKNOWN_SYMBOL;
        }
    }

    tokenList.push_back(Token(TokenType::END_OF_FILE, "\0"));

    return tokenList;
}

//Token::Token(TokenType type, string content, Position startPosition, Position closePosition)

Token Tokenizer::tokenizeQualifier(CharacterReader &reader)
{
    if (isdigit(reader.peek())) return Tokenizer::tokenizeNumberLiteral(reader, 1);
    return Token(TokenType::QUALIFIER, ".");
}

Token Tokenizer::tokenizeComment(CharacterReader &reader)
{
    stringstream commentStream;

    do commentStream << reader.next();
    while (reader.curr() != '#');

    string comment = commentStream.str();

    return Token(TokenType::COMMENT, comment.substr(1, comment.length() - 2));
}

Token Tokenizer::tokenizeNumberLiteral(CharacterReader &reader, int decimalCount)
{
    stringstream number;
    number << reader.curr();

    while (reader.peek() && (isdigit(reader.peek()) || reader.peek() == '.'))
    {
        if (reader.peek() == '.')
        {
            if (++decimalCount > 1) break;
        }

        number << reader.next();
    }

    return Token(TokenType::NUMBER, number.str());
}

Token Tokenizer::tokenizeStringLiteral(CharacterReader &reader)
{
    stringstream stringLiteralStream;


    do stringLiteralStream << reader.next();
    while (reader.curr() != '"');

    string stringLiteral = stringLiteralStream.str();

    return Token(TokenType::STRING, stringLiteral.substr(0, stringLiteral.length() - 1));
}

Token Tokenizer::tokenizeOperation(CharacterReader &reader)
{
    if (reader.peek()) {
        const int operatorsLength = 11;

        const char *doubleCharacterOperators[operatorsLength] = {"+=", "-=", "*=", "/=", ">=", "<=", "==", "!=", "&&", "||", "!!"};

        string possibleOperator = reader.curr_str() + reader.peek_str();

        for (int i=0; i<operatorsLength; i++)
        {
            if (possibleOperator == doubleCharacterOperators[i])
            {
                reader.next();
                return Token(fromDoubleOperation(doubleCharacterOperators[i]), doubleCharacterOperators[i]);
            }
        }
    }

    const int operatorsLength = 12;

    const char *singleCharacterOperators[operatorsLength] = {"!", "+", "-", "*", "/", ">", "<", ",", "(", ")", "{", "}"};

    for (int i=0; i<operatorsLength; i++)
    {
        if (reader.curr_str() == singleCharacterOperators[i])
        {
            return Token(fromSingleOperation(*singleCharacterOperators[i]), string(singleCharacterOperators[i]));
        }
    }

    throw Exception::UNKNOWN_OPERATOR;
}

Token Tokenizer::tokenizeIdentifier(CharacterReader &reader)
{
    stringstream identifierStream;
    identifierStream << reader.curr();

    while (reader.peek() && (isalnum(reader.peek()) || reader.peek() == '_'))
    {
        identifierStream << reader.next();
    }

    string identifier = identifierStream.str();

    if (identifier == "true" || identifier == "false")
        return Token(TokenType::BOOLEAN, identifier);

    const int keywordsLength = 4;

    const char *keywordIdentifiers[keywordsLength] = {"if", "then", "or", "loop"};

    for (int i=0; i<keywordsLength; i++)
    {
        if (identifier == keywordIdentifiers[i]) {
            fromKeyword(keywordIdentifiers[i]);

            return Token(fromKeyword(keywordIdentifiers[i]), keywordIdentifiers[i]);
        }
    }

    return Token(TokenType::IDENTIFIER, identifier);
}

TokenType::TokenType fromSingleOperation(char operation)
{
    switch (operation) {
        case '+': return TokenType::OPERATOR_ADD;
        case '-': return TokenType::OPERATOR_SUB;
        case '*': return TokenType::OPERATOR_MUL;
        case '/': return TokenType::OPERATOR_DIV;
        case '!': return TokenType::DEFINITION;
        case '>': return TokenType::OPERATOR_MORE_THAN;
        case '<': return TokenType::OPERATOR_LESS_THAN;
        case ',': return TokenType::SEPARATOR;
        case '(': return TokenType::L_PAREN;
        case ')': return TokenType::R_PAREN;
        case '$': return TokenType::PARAMETER;
        case '{': return TokenType::L_BLOCK_BRACKET;
        case '}': return TokenType::R_BLOCK_BRACKET;
        default: return TokenType::UNKNOWN;
    }
}

TokenType::TokenType fromDoubleOperation(string operation)
{
    if (operation == "+=") return TokenType::OPERATOR_ADD_EQUAL;
    if (operation == "-=") return TokenType::OPERATOR_SUB_EQUAL;
    if (operation == "*=") return TokenType::OPERATOR_MUL_EQUAL;
    if (operation == "/=") return TokenType::OPERATOR_DIV_EQUAL;
    if (operation == ">=") return TokenType::OPERATOR_MORE_EQUAL;
    if (operation == "<=") return TokenType::OPERATOR_LESS_EQUAL;
    if (operation == "==") return TokenType::OPERATOR_EQUAL;
    if (operation == "!=") return TokenType::OPERATOR_NOT_EQUAL;
    if (operation == "&&") return TokenType::LOGICAL_AND;
    if (operation == "||") return TokenType::LOGICAL_OR;
    if (operation == "!!") return TokenType::STATIC;
    return TokenType::UNKNOWN;
}

TokenType::TokenType fromKeyword(string keyword)
{
    if (keyword == "if") return TokenType::CONDITION;
    if (keyword == "or") return TokenType::OR;
    if (keyword == "then") return TokenType::THEN;
    if (keyword == "loop") return TokenType::LOOP;
    if (keyword == "static") return TokenType::STATIC;
    return TokenType::UNKNOWN;
}