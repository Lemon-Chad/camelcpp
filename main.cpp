#include <iostream>
#include <vector>

#include "source/token/Tokenizer.cpp"
#include "source/Parser.cpp"
#include "source/runtime/Interpreter.cpp"

using namespace std;

const string CAMEL_VERSION = "Beta 1.0.0";

int main(int argumentCount, char *arguments[]) {
    if (argumentCount < 2) {
        cout << "Please provide a filename to run." << endl;
        return -1;
    }

    string programFileName = arguments[1];

    ifstream programFile;
    programFile.open(programFileName, ios::in);

    if (!programFile.is_open()) {
        cout << "The specified programFile \"" << programFileName << "\" does not exist." << endl;
        return -2;
    }

    // Camel Language Implementation
    vector<Token> tokenList = Tokenizer::tokenize(programFile);

    programFile.close();

    for (int i=0; i<tokenList.size(); ++i) {
        Token token = tokenList[i];

        if (token.isWhitespace() || token.getType() == TokenType::COMMENT) {
            tokenList.erase(tokenList.begin() + i);
            i--;
            continue;
        }
    }

    TokenIterator tokenIterator = TokenIterator(tokenList);

    NodeCompoundStatement compoundStatement = *Parser::parse(tokenIterator);

    Interpreter::interpret(compoundStatement);

    return 0;
}