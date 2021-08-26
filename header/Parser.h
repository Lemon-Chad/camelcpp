#ifndef CAMELCPP_PARSER_H
#define CAMELCPP_PARSER_H

#include "node/Node.h"
#include "token/TokenIterator.h"
#include "node/NodeCompoundStatement.h"

class Parser {
public:
    static NodeCompoundStatement* parse(TokenIterator &);
};


#endif //CAMELCPP_PARSER_H
