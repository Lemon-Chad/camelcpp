#include <sstream>
#include "../../header/token/Tokenizer.h"
#include "../CharacterReader.cpp"
#include "Token.cpp"

using namespace std;

static TokenType::TokenType fromSingleOperation(char);
static TokenType::TokenType fromDoubleOperation(string);
static TokenType::TokenType fromKeyword(string);

static Token tokenizeQualifier(CharacterReader &);
static Token tokenizeComment(CharacterReader &);
static Token tokenizeNumberLiteral(CharacterReader &, int);
static vector<Token> tokenizeStringLiteral(CharacterReader &);
static Token tokenizeOperation(CharacterReader &);
static Token tokenizeIdentifier(CharacterReader &);

static const string OPERATION_CHARACTERS = "!?>+-*/^<=,(){}|&";

vector<Token> Tokenizer::tokenize(basic_istream<char>* &inputStream) {
    CharacterReader reader = CharacterReader(inputStream);

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
            for (auto & stringComponent : tokenizeStringLiteral(reader))
                tokenList.push_back(stringComponent);
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
            throw "UnknownSymbol";
        }
    }

    tokenList.push_back(Token(TokenType::END_OF_FILE, "\0"));

    return tokenList;
}

static Token tokenizeQualifier(CharacterReader &reader) {
    if (isdigit(reader.peek())) return tokenizeNumberLiteral(reader, 1);
    return Token(TokenType::QUALIFIER, ".");
}

static Token tokenizeComment(CharacterReader &reader) {
    stringstream commentStream;

    do commentStream << reader.next();
    while (reader.curr() != '#');

    string comment = commentStream.str();

    return Token(TokenType::COMMENT, comment.substr(1, comment.length() - 2));
}

static Token tokenizeNumberLiteral(CharacterReader &reader, int decimalCount) {
    stringstream number;
    number << reader.curr();

    while (reader.peek() && (isdigit(reader.peek()) || reader.peek() == '.')) {
        if (reader.peek() == '.')
            if (++decimalCount > 1) break;

        number << reader.next();
    }

    return Token(TokenType::NUMBER, number.str());
}

static vector<Token> tokenizeStringLiteral(CharacterReader &reader) {
    stringstream stringLiteralStream;

    vector<Token> tokenList;

    bool formatString = false;

    while (true) {
        reader.next_str();

        if (reader.curr() == '\\') {
            bool successfulEscape = false;

            const int escapeCharactersLength = 3;
            const char *escapeCharacters[escapeCharactersLength] = {"n", "\"", "\\"};
            const char *escapeReplacements[escapeCharactersLength] = {"\n", "\"", "\\"};

            for (int i=0; i<escapeCharactersLength; i++) {
                if (reader.peek_str() == escapeCharacters[i]) {
                    stringLiteralStream << escapeReplacements[i];
                    reader.next();
                    successfulEscape = true;
                    break;
                }
            }

            if (!successfulEscape && reader.peek() == '{') {
                stringstream formatExpression;

                tokenList.emplace_back(TokenType::FORMAT_STRING, stringLiteralStream.str());
                stringLiteralStream.str(string());

                reader.next();
                while (reader.next() != '}')
                    formatExpression << reader.curr();

                istringstream* iformatExpression = new istringstream(formatExpression.str());

                vector<Token> expressionTokenList = Tokenizer::tokenize(reinterpret_cast<basic_istream<char> *&>(iformatExpression));

                tokenList.push_back(Token(TokenType::L_FORMAT_EXPRESSION, "{"));

                for (int i=0; i<expressionTokenList.size()-1; i++) tokenList.push_back(expressionTokenList[i]);

                tokenList.push_back(Token(TokenType::R_FORMAT_EXPRESSION, "}"));

                successfulEscape = true;
                formatString = true;
            }

            if (!successfulEscape) throw "InvalidStringEscape";
        }
        else if (reader.curr() == '"') {
            string stringLiteral = stringLiteralStream.str();
            if (!stringLiteral.empty())
                tokenList.push_back(Token(formatString ? TokenType::FORMAT_STRING : TokenType::STRING, stringLiteral));

            return tokenList;
        }
        else stringLiteralStream << reader.curr();
    }
}

static Token tokenizeOperation(CharacterReader &reader) {
    if (reader.peek()) {
        const int operatorsLength = 11;

        const char *doubleCharacterOperators[operatorsLength] = {"+=", "-=", "*=", "/=", ">=", "<=", "==", "!=", "&&", "||", "!!"};

        string possibleOperator = reader.curr_str() + reader.peek_str();

        for (int i=0; i<operatorsLength; i++) {
            if (possibleOperator == doubleCharacterOperators[i]) {
                reader.next();
                return Token(fromDoubleOperation(doubleCharacterOperators[i]), doubleCharacterOperators[i]);
            }
        }
    }

    const int operatorsLength = 13;

    const char *singleCharacterOperators[operatorsLength] = {"!", "+", "-", "*", "/", ">", "<", ",", "(", ")", "{", "}", "&"};

    for (int i=0; i<operatorsLength; i++) {
        if (reader.curr_str() == singleCharacterOperators[i])
            return Token(fromSingleOperation(*singleCharacterOperators[i]), string(singleCharacterOperators[i]));
    }

    throw "UnknownOperator";
}

static Token tokenizeIdentifier(CharacterReader &reader) {
    stringstream identifierStream;
    identifierStream << reader.curr();

    while (reader.peek() && (isalnum(reader.peek()) || reader.peek() == '_'))
        identifierStream << reader.next();

    string identifier = identifierStream.str();

    if (identifier == "true" || identifier == "false")
        return Token(TokenType::BOOLEAN, identifier);

    const int keywordsLength = 4;

    const char *keywordIdentifiers[keywordsLength] = {"if", "then", "or", "loop"};

    for (int i=0; i<keywordsLength; i++) {
        if (identifier == keywordIdentifiers[i]) {
            fromKeyword(keywordIdentifiers[i]);

            return Token(fromKeyword(keywordIdentifiers[i]), keywordIdentifiers[i]);
        }
    }

    return Token(TokenType::IDENTIFIER, identifier);
}

static TokenType::TokenType fromSingleOperation(char operation)
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
        case '&': return TokenType::REFERENCE;
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