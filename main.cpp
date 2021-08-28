#include <iostream>
#include <iomanip>
#include <vector>
#include <cstring>
#include <chrono>

#include "source/token/Tokenizer.cpp"
#include "source/Parser.cpp"
#include "source/runtime/Interpreter.cpp"

using namespace std;

const string CAMEL_VERSION = "Beta 1.0.0";

struct ProgramFlags {
    bool v;
    bool t;
    bool p;
    bool h;
};

int main(int argumentCount, char *arguments[]) {
    auto milliseconds1 = chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now().time_since_epoch()).count();

    ProgramFlags programFlags= {false, false, false, false};

    int argumentIndex = 1;
    for (; argumentIndex<argumentCount; ++argumentIndex) {
        if (strcmp(arguments[argumentIndex], "-v") == 0)
            programFlags.v = true;
        else if (strcmp(arguments[argumentIndex], "-t") == 0)
            programFlags.t = true;
        else if (strcmp(arguments[argumentIndex], "-p") == 0)
            programFlags.p = true;
        else if (strcmp(arguments[argumentIndex], "-h") == 0)
            programFlags.h = true;
        else break;
    }

    if (programFlags.v) {
        cout << CAMEL_VERSION << endl;
        return 1;
    }

    if (programFlags.h) {
        cout << "camel <-v|-t|-p|-h> <programFile>" << endl;
        return 2;
    }

    if (argumentIndex == argumentCount) {
        cout << "Please provide a filename to run." << endl;
        return -1;
    }

    string programFileName = arguments[argumentIndex];

    ifstream* programFile = new ifstream();
    programFile->open(programFileName, ios::in);

    if (!programFile->is_open()) {
        cout << "The specified programFile \"" << programFileName << "\" does not exist." << endl;
        return -2;
    }

    // Camel Language Implementation
    vector<Token> tokenList = Tokenizer::tokenize(reinterpret_cast<basic_istream<char> *&>(programFile));

    programFile->close();

    for (int i=0; i<tokenList.size(); ++i) {
        Token token = tokenList[i];

        if (token.isWhitespace() || token.getType() == TokenType::COMMENT) {
            tokenList.erase(tokenList.begin() + i);
            i--;
            continue;
        }
    }

    if (programFlags.t) {
        for (auto &token : tokenList)
            cout << left << setw(40) << ("TokenType::" + Helper::tokenTypeName(token.getType())) << " Content: \"" << token.getContent() << "\"" << endl;

        cout << "Tokenized: " << tokenList.size() << endl;

        return 3;
    }

    TokenIterator tokenIterator = TokenIterator(tokenList);

    NodeCompoundStatement compoundStatement = *Parser::parse(tokenIterator);

    Interpreter::interpret(compoundStatement);

    auto milliseconds2 = chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now().time_since_epoch()).count();

    if (programFlags.p) {
        cout << "Total time running: " << (milliseconds2 - milliseconds1) << "ms" << endl;
    }

    return 0;
}