#include <sstream>
#include "../header/CharacterReader.h"
#include <string>

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

    inputStream->get(previewCharacter);
    inputStream->putback(previewCharacter);

    if (inputStream->fail() || inputStream->eof()) return 0;

    return previewCharacter;
}

string CharacterReader::curr_str()
{
    stringstream stream;
    stream << curr();

    return stream.str();
}

string CharacterReader::peek_str()
{
    stringstream stream;
    stream << peek();

    return stream.str();
}

string CharacterReader::next_str()
{
    stringstream stream;
    stream << next();

    return stream.str();
}