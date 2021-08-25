#include "../../header/token/TokenIterator.h"

TokenIterator::TokenIterator(vector<Token> &tokenList) : tokenList(tokenList) {}

Token TokenIterator::next() {
    index++;
    return curr();
}

Token TokenIterator::prev() {
    return tokenList[index-1];
}

Token TokenIterator::peek() {
    return tokenList[index+1];
}

Token TokenIterator::curr() {
    return tokenList[index];
}

int TokenIterator::currentIndex() {
    return index;
}

void TokenIterator::reset(int index) {
    this->index = index;
}

bool TokenIterator::hasNext() {
    return index+1 < tokenList.size();
}