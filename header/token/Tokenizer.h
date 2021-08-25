#ifndef CAMELCPP_TOKENIZER_H
#define CAMELCPP_TOKENIZER_H

#include <vector>
#include <iostream>
#include <fstream>
#include <list>
#include "Token.h"
#include "../CharacterReader.h"

using namespace std;


class Tokenizer {

public:
    static vector<Token> tokenize(ifstream &reader);

private:
    static Token tokenizeQualifier(CharacterReader &);
    static Token tokenizeComment(CharacterReader &);
    static Token tokenizeNumberLiteral(CharacterReader &, int);
    static Token tokenizeStringLiteral(CharacterReader &);
    static Token tokenizeOperation(CharacterReader &);
    static Token tokenizeIdentifier(CharacterReader &);
};


#endif //CAMELCPP_TOKENIZER_H
