#ifndef CAMELCPP_TOKENITERATOR_H
#define CAMELCPP_TOKENITERATOR_H

#include <vector>


class TokenIterator {
private:
    const vector<Token> tokenList;
    int index = 0;

public:
    TokenIterator(vector<Token> &);

    Token next();
    Token prev();
    Token peek();
    Token curr();

    int currentIndex();

    void reset(int);

    bool hasNext();
};


#endif //CAMELCPP_TOKENITERATOR_H
