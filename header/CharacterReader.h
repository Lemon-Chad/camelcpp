#ifndef CAMELCPP_CHARACTERREADER_H
#define CAMELCPP_CHARACTERREADER_H

#include <fstream>
#include <string>

class CharacterReader {
private:
    char currentCharacter;
    basic_istream<char>* inputStream;

public:
    CharacterReader(basic_istream<char>* &inputFileStream);

    char curr();
    char peek();
    char next();

    string curr_str();
    string peek_str();
    string next_str();
};


#endif //CAMELCPP_CHARACTERREADER_H
