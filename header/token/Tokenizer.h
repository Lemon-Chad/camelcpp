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
    static vector<Token> tokenize(basic_istream<char>* &);
};


#endif //CAMELCPP_TOKENIZER_H
