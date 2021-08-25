#ifndef CAMELCPP_CHARACTERREADER_H
#define CAMELCPP_CHARACTERREADER_H

#include <fstream>

class CharacterReader {
private:
    char currentCharacter;
    ifstream &inputFileStream;

public:
    CharacterReader(ifstream &inputFileStream);

    char curr();
    char peek();
    char next();

    string curr_str();
    string peek_str();
    string next_str();
};


#endif //CAMELCPP_CHARACTERREADER_H
