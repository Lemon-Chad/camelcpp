#include "../../header/node/NodeInvocationStatement.h"
#include "../../header/function/Function.h"


NodeInvocationStatement::NodeInvocationStatement(NodeVariable variable, NodeArgumentList argumentList)
        : variable(variable), argumentList(argumentList) {}

Value * NodeInvocationStatement::interpret(RuntimeEnvironment &environment, RuntimeContext &context) {
    vector<string> identifiers = variable.getIdentifiers();

    vector<Value *> arguments;

    for (Node *argumentNode : argumentList.getArgumentList())
        arguments.push_back(argumentNode->interpret(environment, context));

    if (identifiers.size() == 1 && identifiers[0] == "return") {
        return new LiteralReturn(arguments[0]);
    }

    Value *variableValue = variable.interpret(environment, context);

    if (dynamic_cast<Function *>(variableValue)) {
        Function *function = dynamic_cast<Function *>(variableValue);

        return function->invokeFunction(environment, arguments);
    }

    string ident = identifiers[0];

    if (arguments.empty())
        context.accessField(identifiers)->setValue(nullptr);

    context.accessField(identifiers)->setValue(arguments[0]);
    return arguments[0];
}