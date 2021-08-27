#include <sstream>
#include "../header/CharacterReader.h"

using namespace std;

CharacterReader::CharacterReader(basic_istream<char>* &inputStream) : inputStream(inputStream) {}

char CharacterReader::curr()
{
    return currentCharacter;
}

char CharacterReader::next()
{
    inputStream->get(currentCharacter);

    return currentCharacter;
}

char CharacterReader::peek()
{
    char previewCharacter;

    int marker = inputStream->tellg();

    inputStream->get(previewCharacter);

    inputStream->seekg(marker);

    if (inputStream->fail() || inputStream->eof()) return 0;

    return previewCharacter;
}

string CharacterReader::curr_str()
{
    std::stringstream stream;
    stream << curr();

    return stream.str();
}

string CharacterReader::peek_str()
{
    std::stringstream stream;
    stream << peek();

    return stream.str();
}

string CharacterReader::next_str()
{
    std::stringstream stream;
    stream << next();

    return stream.str();
}