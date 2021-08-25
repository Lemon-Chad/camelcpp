#include <vector>

#include "../header/Parser.h"
#include "../source/Conditional.cpp"

#include "../source/node/NodeArgumentList.cpp"
#include "../source/node/NodeBoolean.cpp"
#include "../source/node/NodeCompoundStatement.cpp"
#include "../source/node/NodeConditionalStatement.cpp"
#include "../source/node/NodeDecimal.cpp"
#include "../source/node/NodeEnclosedCompoundStatement.cpp"
#include "../source/node/NodeExpression.cpp"
#include "../source/node/NodeVariable.cpp"
#include "../source/node/NodeFunctionDeclarationStatement.cpp"
#include "../source/node/NodeInteger.cpp"
#include "../source/node/NodeInvocationStatement.cpp"
#include "../source/node/NodeLoopStatement.cpp"
#include "../source/node/NodeStaticDeclarationStatement.cpp"
#include "../source/node/NodeString.cpp"
#include "../source/node/NodeUnaryExpression.cpp"
#include "../source/node/NodeVariableDeclarationStatement.cpp"

#include "../source/Helper.cpp"
#include "../source/Operand.cpp"
#include "../source/token/TokenIterator.cpp"

using namespace std;

static const string parseIdentifier(TokenIterator &);
static vector<string>* parseQualifiedIdentifier(TokenIterator &);
static NodeVariable* parseVariable(TokenIterator &);
static NodeDecimal* parseDecimal(TokenIterator &);
static NodeInteger* parseInteger(TokenIterator &);
static NodeBoolean* parseBoolean(TokenIterator &);
static NodeString* parseString(TokenIterator &);
static Node* parseLiteral(TokenIterator &);
static NodeNumber* parseNumber(TokenIterator &);
static NodeUnaryExpression* parseUnaryExpression(TokenIterator &);
static Operation::Operation fromTokenType(TokenType::TokenType);
static Node* parseTerm(TokenIterator &);
static NodeArgumentList* parseArgumentList(TokenIterator &);
static Node* parseEnclosedExpression(TokenIterator &);
static Node* parseExpression(TokenIterator &);
static Node* parseComparisonExpression(TokenIterator &);
static Node* parseArithmeticExpression(TokenIterator &);
static Node* parseArithmeticTerm0(TokenIterator &);
static NodeConditionalStatement* parseConditionalStatement(TokenIterator &);
static NodeStatement* parseStatement(TokenIterator &);
static NodeCompoundStatement* parseCompoundStatement(TokenIterator &);
static NodeEnclosedCompoundStatement* parseEnclosedCompoundStatement(TokenIterator &);
static NodeStaticDeclarationStatement* parseStaticDeclarationStatement(TokenIterator &);
static NodeVariableDeclarationStatement* parseVariableDeclarationStatement(TokenIterator &);
static NodeFunctionDeclarationStatement* parseFunctionDeclarationStatement(TokenIterator &);
static NodeInvocationStatement* parseInvocationStatement(TokenIterator &);
static NodeLoopStatement* parseLoopStatement(TokenIterator &);

static bool isUnaryOperation(Operation::Operation operation);
static bool isLogicalOperation(Operation::Operation operation);
static bool isComparisonOperation(Operation::Operation operation);
static bool isArithmeticOperation0(Operation::Operation operation);
static bool isArithmeticOperation1(Operation::Operation operation);


NodeCompoundStatement* Parser::parse(TokenIterator &tokenIterator) {
    return parseCompoundStatement(tokenIterator);
}

static NodeStatement* parseStatement(TokenIterator &tokenIterator) {
    int marker = tokenIterator.currentIndex();

    NodeStatement* statement;

    if ((statement = parseEnclosedCompoundStatement(tokenIterator)) != nullptr)
        return statement;

    if ((statement = parseVariableDeclarationStatement(tokenIterator)) != nullptr)
        return statement;

    if ((statement = parseFunctionDeclarationStatement(tokenIterator)) != nullptr)
        return statement;

    if ((statement = parseInvocationStatement(tokenIterator)) != nullptr)
        return statement;

    if ((statement = parseConditionalStatement(tokenIterator)) != nullptr)
        return statement;

    if ((statement = parseLoopStatement(tokenIterator)) != nullptr)
        return statement;

    if ((statement = parseStaticDeclarationStatement(tokenIterator)) != nullptr)
        return statement;

    tokenIterator.reset(marker);
    return nullptr;
}

static NodeCompoundStatement* parseCompoundStatement(TokenIterator &tokenIterator) {
    NodeStatement* statement = parseStatement(tokenIterator);

    if (statement == nullptr)
        return new NodeCompoundStatement(list<NodeStatement*>());

    list<NodeStatement*> statementList;
    statementList.push_back(statement);

    while (tokenIterator.hasNext()) {
        int internalMarker = tokenIterator.currentIndex();

        NodeStatement* internalStatement = parseStatement(tokenIterator);

        if (internalStatement == nullptr) {
            tokenIterator.reset(internalMarker);
            break;
        }

        statementList.push_back(internalStatement);
    }

    return new NodeCompoundStatement(statementList);
}

static NodeStaticDeclarationStatement* parseStaticDeclarationStatement(TokenIterator &tokenIterator) {
    int marker = tokenIterator.currentIndex();

    if (tokenIterator.curr().getType() != TokenType::STATIC) {
        tokenIterator.reset(marker);
        return nullptr;
    }

    tokenIterator.next();

    const string identifier = parseIdentifier(tokenIterator);

    if (identifier.empty()) {
        tokenIterator.reset(marker);
        return nullptr;
    }

    NodeEnclosedCompoundStatement* compoundStatement = parseEnclosedCompoundStatement(tokenIterator);

    if (compoundStatement == nullptr) {
        tokenIterator.reset(marker);
        return nullptr;
    }

    return new NodeStaticDeclarationStatement(identifier, compoundStatement);
}

static NodeEnclosedCompoundStatement* parseEnclosedCompoundStatement(TokenIterator &tokenIterator)
{
    int marker = tokenIterator.currentIndex();

    if (tokenIterator.curr().getType() != TokenType::L_BLOCK_BRACKET)
    {
        tokenIterator.reset(marker);
        return nullptr;
    }

    tokenIterator.next();

    NodeCompoundStatement* compoundStatement = parseCompoundStatement(tokenIterator);

    if (tokenIterator.curr().getType() != TokenType::R_BLOCK_BRACKET)
    {
        tokenIterator.reset(marker);
        return nullptr;
    }

    tokenIterator.next();
    return new NodeEnclosedCompoundStatement(compoundStatement);
}

static NodeConditionalStatement* parseConditionalStatement(TokenIterator &tokenIterator) {
    int marker = tokenIterator.currentIndex();

    if (tokenIterator.curr().getType() != TokenType::CONDITION)
    {
        tokenIterator.reset(marker);
        return nullptr;
    }

    tokenIterator.next();

    Node* expression = parseExpression(tokenIterator);

    if (expression == nullptr)
    {
        tokenIterator.reset(marker);
        return nullptr;
    }

    if (tokenIterator.curr().getType() != TokenType::THEN)
    {
        tokenIterator.reset(marker);
        return nullptr;
    }

    tokenIterator.next();

    NodeEnclosedCompoundStatement* compoundStatement = parseEnclosedCompoundStatement(tokenIterator);

    if (compoundStatement == nullptr) {
        tokenIterator.reset(marker);
        return nullptr;
    }

    Conditional *conditional = new Conditional(expression, compoundStatement);

    list<Conditional*> conditionalList;

    while (tokenIterator.hasNext()) {
        int internalMarker = tokenIterator.currentIndex();

        if (tokenIterator.curr().getType() != TokenType::OR) {
            tokenIterator.reset(internalMarker);
            break;
        }

        tokenIterator.next();

        if (tokenIterator.curr().getType() != TokenType::CONDITION) {
            tokenIterator.reset(internalMarker);
            break;
        }

        tokenIterator.next();

        Node* internalExpression = parseExpression(tokenIterator);

        if (internalExpression == nullptr) {
            tokenIterator.reset(internalMarker);
            break;
        }

        if (tokenIterator.curr().getType() != TokenType::THEN) {
            tokenIterator.reset(internalMarker);
            break;
        }

        tokenIterator.next();

        NodeEnclosedCompoundStatement* internalCompoundStatement = parseEnclosedCompoundStatement(tokenIterator);

        if (internalCompoundStatement == nullptr) {
            tokenIterator.reset(internalMarker);
            break;
        }

        conditionalList.push_back(new Conditional(internalExpression, internalCompoundStatement));
    }

    int defaultMarker = tokenIterator.currentIndex();

    if (tokenIterator.curr().getType() != TokenType::OR)
    {
        tokenIterator.reset(defaultMarker);
        return new NodeConditionalStatement(conditional, nullptr, conditionalList);
    }

    tokenIterator.next();

    NodeEnclosedCompoundStatement* defaultCompoundStatement = parseEnclosedCompoundStatement(tokenIterator);

    if (defaultCompoundStatement == nullptr)
    {
        tokenIterator.reset(defaultMarker);
        return new NodeConditionalStatement(conditional, nullptr, conditionalList);
    }

    Node* nullNode = nullptr;
    Conditional *defaultConditional = new Conditional(nullNode, defaultCompoundStatement);

    return new NodeConditionalStatement(conditional, defaultConditional, conditionalList);
}

static NodeVariableDeclarationStatement* parseVariableDeclarationStatement(TokenIterator &tokenIterator) {
    int marker = tokenIterator.currentIndex();

    if (tokenIterator.curr().getType() != TokenType::DEFINITION) {
        tokenIterator.reset(marker);
        return nullptr;
    }

    tokenIterator.next();

    vector<string>* variable = parseQualifiedIdentifier(tokenIterator);

    if (variable == nullptr) {
        tokenIterator.reset(marker);
        return nullptr;
    }

    Node* expression = parseEnclosedExpression(tokenIterator);

    if (expression == nullptr) {
        tokenIterator.reset(marker);
        return nullptr;
    }

    return new NodeVariableDeclarationStatement(*variable, expression);
}

static NodeFunctionDeclarationStatement* parseFunctionDeclarationStatement(TokenIterator &tokenIterator) {
    int marker = tokenIterator.currentIndex();

    if (tokenIterator.curr().getType() != TokenType::DEFINITION) {
        tokenIterator.reset(marker);
        return nullptr;
    }

    tokenIterator.next();

    NodeVariable* variable = parseVariable(tokenIterator);

    if (variable == nullptr) {
        tokenIterator.reset(marker);
        return nullptr;
    }

    NodeEnclosedCompoundStatement* compoundStatement = parseEnclosedCompoundStatement(tokenIterator);

    if (compoundStatement == nullptr) {
        tokenIterator.reset(marker);
        return nullptr;
    }

    return new NodeFunctionDeclarationStatement(*variable, *compoundStatement);
}

static NodeInvocationStatement* parseInvocationStatement(TokenIterator &tokenIterator) {
    int marker = tokenIterator.currentIndex();

    NodeVariable* variable = parseVariable(tokenIterator);

    if (variable == nullptr) {
        tokenIterator.reset(marker);
        return nullptr;
    }

    if (tokenIterator.curr().getType() != TokenType::L_PAREN) {
        tokenIterator.reset(marker);
        return nullptr;
    }

    tokenIterator.next();

    NodeArgumentList* argumentList = parseArgumentList(tokenIterator);

    if (tokenIterator.curr().getType() != TokenType::R_PAREN) {
        tokenIterator.reset(marker);
        return nullptr;
    }

    tokenIterator.next();
    return new NodeInvocationStatement(*variable, *argumentList);
}

static NodeLoopStatement* parseLoopStatement(TokenIterator &tokenIterator) {
    int marker = tokenIterator.currentIndex();

    if (tokenIterator.curr().getType() != TokenType::LOOP) {
        tokenIterator.reset(marker);
        return nullptr;
    }

    tokenIterator.next();

    Node* expression = parseExpression(tokenIterator);

    if (expression == nullptr) {
        tokenIterator.reset(marker);
        return nullptr;
    }

    if (tokenIterator.curr().getType() != TokenType::THEN) {
        tokenIterator.reset(marker);
        return nullptr;
    }

    tokenIterator.next();

    NodeEnclosedCompoundStatement* compoundStatement = parseEnclosedCompoundStatement(tokenIterator);

    if (compoundStatement == nullptr) {
        tokenIterator.reset(marker);
        return nullptr;
    }

    return new NodeLoopStatement(expression, *compoundStatement);
}

static Node* parseArithmeticTerm0(TokenIterator &tokenIterator) {
    int marker = tokenIterator.currentIndex();

    Node* term = parseTerm(tokenIterator);

    if (term == nullptr) {
        tokenIterator.reset(marker);
        return nullptr;
    }

    list<Operand> operandList;

    while (tokenIterator.hasNext()) {
        int internalMarker = tokenIterator.currentIndex();

        Operation::Operation operation = fromTokenType(tokenIterator.curr().getType());

        if (operation != Operation::UNKNOWN && isArithmeticOperation0(operation)) {
            tokenIterator.next();

            Node* internalTerm = parseTerm(tokenIterator);

            if (internalTerm == nullptr) {
                tokenIterator.reset(internalMarker);
                break;
            }

            operandList.push_back(Operand(operation, internalTerm));
        }
        else {
            tokenIterator.reset(internalMarker);
            break;
        }
    }

    if (operandList.empty())
        return term;

    return new NodeExpression(term, operandList);
}

static Node* parseArithmeticExpression(TokenIterator &tokenIterator)
{
    int marker = tokenIterator.currentIndex();

    Node* term = parseArithmeticTerm0(tokenIterator);

    if (term == nullptr) {
        tokenIterator.reset(marker);
        return nullptr;
    }

    list<Operand> operandList;

    while (tokenIterator.hasNext())
    {
        int internalMarker = tokenIterator.currentIndex();

        Operation::Operation operation = fromTokenType(tokenIterator.curr().getType());

        if (operation != Operation::UNKNOWN && isArithmeticOperation1(operation)) {
            tokenIterator.next();

            Node* internalTerm = parseArithmeticTerm0(tokenIterator);

            if (internalTerm == nullptr) {
                tokenIterator.reset(internalMarker);
                break;
            }

            operandList.push_back(Operand(operation, internalTerm));
        }
        else {
            tokenIterator.reset(internalMarker);
            break;
        }
    }

    if (operandList.empty())
        return term;

    return new NodeExpression(term, operandList);
}

static Node* parseComparisonExpression(TokenIterator &tokenIterator) {
    int marker = tokenIterator.currentIndex();

    Node* term = parseArithmeticExpression(tokenIterator);

    if (term == nullptr) {
        tokenIterator.reset(marker);
        return nullptr;
    }

    list<Operand> operandList;

    while (tokenIterator.hasNext()) {
        int internalMarker = tokenIterator.currentIndex();

        Operation::Operation operation = fromTokenType(tokenIterator.curr().getType());

        if (operation != Operation::UNKNOWN && isComparisonOperation(operation)) {
            tokenIterator.next();

            Node* internalTerm = parseArithmeticExpression(tokenIterator);

            if (internalTerm == nullptr)
            {
                tokenIterator.reset(internalMarker);
                break;
            }

            operandList.push_back(Operand(operation, internalTerm));
        }
        else
        {
            tokenIterator.reset(internalMarker);
            break;
        }
    }

    if (operandList.empty())
    {
        return term;
    }
    return new NodeExpression(term, operandList);
}

static Node* parseExpression(TokenIterator &tokenIterator) {
    int marker = tokenIterator.currentIndex();

    Node* term = parseComparisonExpression(tokenIterator);

    if (term == nullptr) {
        tokenIterator.reset(marker);
        return nullptr;
    }

    list<Operand> operandList;

    while (tokenIterator.hasNext()) {
        int internalMarker = tokenIterator.currentIndex();

        Operation::Operation operation = fromTokenType(tokenIterator.curr().getType());

        if (operation != Operation::UNKNOWN && isLogicalOperation(operation)) {
            tokenIterator.next();

            Node* internalTerm = parseComparisonExpression(tokenIterator);

            if (internalTerm == nullptr) {
                tokenIterator.reset(internalMarker);
                break;
            }

            operandList.push_back(Operand(operation, internalTerm));
        }
        else {
            tokenIterator.reset(internalMarker);
            break;
        }
    }

    if (operandList.empty())
        return term;

    return new NodeExpression(term, operandList);
}

static Node* parseEnclosedExpression(TokenIterator &tokenIterator) {
    int marker = tokenIterator.currentIndex();

    if (tokenIterator.curr().getType() != TokenType::L_PAREN) {
        tokenIterator.reset(marker);
        return nullptr;
    }

    tokenIterator.next();
    Node* expression = parseExpression(tokenIterator);

    if (tokenIterator.curr().getType() != TokenType::R_PAREN) {
        tokenIterator.reset(marker);
        return nullptr;
    }

    tokenIterator.next();
    return expression;
}

static NodeArgumentList* parseArgumentList(TokenIterator &tokenIterator) {
    Node* expression = parseExpression(tokenIterator);

    if (expression == nullptr)
        return new NodeArgumentList(vector<Node*>());

    vector<Node*> expressionList;
    expressionList.push_back(expression);

    while (tokenIterator.hasNext()) {
        int internalMarker = tokenIterator.currentIndex();

        if (tokenIterator.curr().getType() != TokenType::SEPARATOR)
            break;

        tokenIterator.next();

        Node* internalExpression = parseExpression(tokenIterator);

        if (internalExpression == nullptr) {
            tokenIterator.reset(internalMarker);
            break;
        }

        expressionList.push_back(internalExpression);
    }

    return new NodeArgumentList(expressionList);
}

static Node* parseTerm(TokenIterator &tokenIterator) {
    int marker = tokenIterator.currentIndex();

    Node* node;

    if ((node = parseUnaryExpression(tokenIterator)) != nullptr)
        return node;

    if ((node = parseLiteral(tokenIterator)) != nullptr)
        return node;

    if ((node = parseInvocationStatement(tokenIterator)) != nullptr)
        return node;

    if ((node = parseVariable(tokenIterator)) != nullptr)
        return node;

    if (tokenIterator.curr().getType() != TokenType::L_PAREN) {
        tokenIterator.reset(marker);
        return nullptr;
    }

    tokenIterator.next();

    Node* expression = parseExpression(tokenIterator);

    if (expression == nullptr)
    {
        tokenIterator.reset(marker);
        return nullptr;
    }

    if (tokenIterator.curr().getType() != TokenType::R_PAREN)
    {
        tokenIterator.reset(marker);
        return nullptr;
    }

    tokenIterator.next();
    return expression;
}

static NodeUnaryExpression* parseUnaryExpression(TokenIterator &tokenIterator) {
    int marker = tokenIterator.currentIndex();

    Operation::Operation operation = fromTokenType(tokenIterator.curr().getType());

    if (operation == Operation::UNKNOWN || !isUnaryOperation(operation)) {
        tokenIterator.reset(marker);
        return nullptr;
    }

    tokenIterator.next();

    Node* term = parseTerm(tokenIterator);

    if (term == nullptr) {
        tokenIterator.reset(marker);
        return nullptr;
    }

    return new NodeUnaryExpression(operation, term);
}

static NodeNumber* parseNumber(TokenIterator &tokenIterator) {
    int marker = tokenIterator.currentIndex();

    NodeNumber* number;

    if ((number = parseInteger(tokenIterator)) != nullptr)
        return number;

    if ((number = parseDecimal(tokenIterator)) != nullptr)
        return number;

    tokenIterator.reset(marker);
    return nullptr;
}

static NodeInteger* parseInteger(TokenIterator &tokenIterator) {
    int marker = tokenIterator.currentIndex();

    if (tokenIterator.curr().getType() != TokenType::NUMBER) {
        tokenIterator.reset(marker);
        return nullptr;
    }

    if (tokenIterator.curr().getContent().find(".") != string::npos) {
        tokenIterator.reset(marker);
        return nullptr;
    }

    tokenIterator.next();
    return NodeInteger::parseInteger(tokenIterator.prev().getContent());
}

static NodeDecimal* parseDecimal(TokenIterator &tokenIterator) {
    int marker = tokenIterator.currentIndex();

    if (tokenIterator.curr().getType() != TokenType::NUMBER) {
        tokenIterator.reset(marker);
        return nullptr;
    }

    tokenIterator.next();
    return NodeDecimal::parseDecimal(tokenIterator.prev().getContent());
}

static NodeBoolean* parseBoolean(TokenIterator &tokenIterator) {
    int marker = tokenIterator.currentIndex();

    if (tokenIterator.curr().getType() != TokenType::BOOLEAN) {
        tokenIterator.reset(marker);
        return nullptr;
    }

    tokenIterator.next();
    return NodeBoolean::parseBoolean(tokenIterator.prev().getContent());
}

static NodeString* parseString(TokenIterator &tokenIterator) {
    int marker = tokenIterator.currentIndex();

    if (tokenIterator.curr().getType() != TokenType::STRING) {
        tokenIterator.reset(marker);
        return nullptr;
    }

    tokenIterator.next();
    return NodeString::parseString(tokenIterator.prev().getContent());
}

static Node* parseLiteral(TokenIterator &tokenIterator)
{
    int marker = tokenIterator.currentIndex();

    Node* node;

    if ((node = parseNumber(tokenIterator)) != nullptr)
        return node;

    if ((node = parseBoolean(tokenIterator)) != nullptr)
        return node;

    if ((node = parseString(tokenIterator)) != nullptr)
        return node;

    tokenIterator.reset(marker);
    return nullptr;
}

static NodeVariable* parseVariable(TokenIterator &tokenIterator) {
    int marker = tokenIterator.currentIndex();

    vector<string>* qualifiedIdentifier = parseQualifiedIdentifier(tokenIterator);

    if (qualifiedIdentifier == nullptr) {
        tokenIterator.reset(marker);
        return nullptr;
    }

    return new NodeVariable(*qualifiedIdentifier);
}

static vector<string>* parseQualifiedIdentifier(TokenIterator &tokenIterator) {
    int marker = tokenIterator.currentIndex();

    const string identifier = parseIdentifier(tokenIterator);

    if (identifier.empty()) {
        tokenIterator.reset(marker);
        return nullptr;
    }

    vector<string>* identifierList = new vector<string>;

    identifierList->push_back(identifier);

    while (tokenIterator.hasNext()) {
        int internalMarker = tokenIterator.currentIndex();

        if (tokenIterator.curr().getType() != TokenType::QUALIFIER) {
            break;
        }

        tokenIterator.next();

        if (tokenIterator.curr().getType() != TokenType::IDENTIFIER) {
            tokenIterator.reset(internalMarker);
            break;
        }

        identifierList->push_back(tokenIterator.curr().getContent());

        tokenIterator.next();
    }

    return identifierList;
}

static const string parseIdentifier(TokenIterator &tokenIterator) {
    int marker = tokenIterator.currentIndex();

    if (tokenIterator.curr().getType() != TokenType::IDENTIFIER) {
        tokenIterator.reset(marker);
        return "";
    }

    string identifier = tokenIterator.curr().getContent();

    tokenIterator.next();
    return identifier;
}

static Operation::Operation fromTokenType(TokenType::TokenType tokenType) {
    switch (tokenType) {
        case TokenType::OPERATOR_ADD: return Operation::ADDITION;
        case TokenType::OPERATOR_SUB: return Operation::SUBTRACTION;
        case TokenType::OPERATOR_NOT: return Operation::UNARY_NOT;

        case TokenType::OPERATOR_MUL: return Operation::MULTIPLICATION;
        case TokenType::OPERATOR_DIV: return Operation::DIVISION;

        case TokenType::OPERATOR_EQUAL: return Operation::EQUAL;
        case TokenType::OPERATOR_NOT_EQUAL: return Operation::NOT_EQUAL;

        case TokenType::OPERATOR_MORE_THAN: return Operation::MORE_THAN;
        case TokenType::OPERATOR_LESS_THAN: return Operation::LESS_THAN;

        case TokenType::OPERATOR_MORE_EQUAL: return Operation::MORE_EQUAL;
        case TokenType::OPERATOR_LESS_EQUAL: return Operation::LESS_EQUAL;

        case TokenType::LOGICAL_AND: return Operation::LOGICAL_AND;
        case TokenType::OR: return Operation::LOGICAL_OR;

        default: break;
    }
    return Operation::UNKNOWN;
}

static bool isUnaryOperation(Operation::Operation operation) {
    if (operation == Operation::ADDITION) return true;
    if (operation == Operation::SUBTRACTION) return true;
    return operation == Operation::UNARY_NOT;
}

static bool isLogicalOperation(Operation::Operation operation) {
    if (operation == Operation::LOGICAL_OR) return true;
    return operation == Operation::LOGICAL_AND;
}

static bool isComparisonOperation(Operation::Operation operation) {
    switch (operation) {
        case Operation::EQUAL:
        case Operation::NOT_EQUAL:
        case Operation::MORE_EQUAL:
        case Operation::LESS_EQUAL:
        case Operation::MORE_THAN:
        case Operation::LESS_THAN:
            return true;
        default:
            return false;
    }
}

static bool isArithmeticOperation1(Operation::Operation operation) {
    if (operation == Operation::ADDITION) return true;
    return operation == Operation::SUBTRACTION;
}

static bool isArithmeticOperation0(Operation::Operation operation) {
    if (operation == Operation::MULTIPLICATION) return true;
    return operation == Operation::DIVISION;
}