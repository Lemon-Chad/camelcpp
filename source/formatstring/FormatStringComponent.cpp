#include "../../header/formatstring/FormatStringComponent.h"


StaticFormatStringComponent::StaticFormatStringComponent(string value): value(value) {}

string StaticFormatStringComponent::interpret(RuntimeEnvironment &environment, RuntimeContext* &context) {
    return value;
}

ExpressionFormatStringComponent::ExpressionFormatStringComponent(Node* &expression): expression(expression) {}

string ExpressionFormatStringComponent::interpret(RuntimeEnvironment &environment, RuntimeContext* &context) {
    return expression->interpret(environment, context)->toString();
}
