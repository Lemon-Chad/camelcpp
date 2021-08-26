#ifndef CAMELCPP_FORMATSTRINGCOMPONENT_H
#define CAMELCPP_FORMATSTRINGCOMPONENT_H


#include "../runtime/RuntimeContext.h"
#include "../node/NodeExpression.h"

class FormatStringComponent {
public:
    virtual string interpret(RuntimeEnvironment &, RuntimeContext &) = 0;
};

class StaticFormatStringComponent: public FormatStringComponent {
private:
    string value;

public:
    StaticFormatStringComponent(string);

    string interpret(RuntimeEnvironment &, RuntimeContext &) override;
};

class ExpressionFormatStringComponent: public FormatStringComponent {
private:
    Node* expression;

public:
    ExpressionFormatStringComponent(Node* &);

    string interpret(RuntimeEnvironment &, RuntimeContext &) override;
};


#endif //CAMELCPP_FORMATSTRINGCOMPONENT_H
