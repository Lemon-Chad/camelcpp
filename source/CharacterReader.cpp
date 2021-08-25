#include <sstream>
#include "../header/CharacterReader.h"

using namespace std;

CharacterReader::CharacterReader(ifstream &inputFileStream_)
        : inputFileStream(inputFileStream_) {}

char CharacterReader::curr()
{
    return currentCharacter;
}

char CharacterReader::next()
{
    inputFileStream.get(currentCharacter);

    return currentCharacter;
}

char CharacterReader::peek()
{
    char previewCharacter;

    int marker = inputFileStream.tellg();

    inputFileStream.get(previewCharacter);

    inputFileStream.seekg(marker);

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